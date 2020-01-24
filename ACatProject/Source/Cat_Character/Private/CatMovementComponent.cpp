// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved


#include "CatMovementComponent.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "CatCapsuleComponent.h"
#include "GameFramework/Controller.h"

#if !UE_BUILD_SHIPPING
#include "DrawDebugHelpers.h"
#endif

// TODO : may not be a good think to just copy the define/declares
DEFINE_LOG_CATEGORY_STATIC(LogCharacterMovement, Log, All);
DECLARE_CYCLE_STAT(TEXT("Char CharStepUp"), STAT_CharStepUp, STATGROUP_Character);
//
// MAGIC NUMBERS (from CharacterMovementComponent)
const float MAX_STEP_SIDE_Z = 0.08f;	// maximum z value for the normal on the vertical side of steps
const float SWIMBOBSPEED = -80.f;
const float VERTICAL_SLOPE_NORMAL_Z = 0.001f; // Slope is vertical if Abs(Normal.Z) <= this threshold. Accounts for precision problems that sometimes angle normals slightly off horizontal for vertical surface.



float UCatMovementComponent::MinMovingSpeed = KINDA_SMALL_NUMBER;

UCatMovementComponent::UCatMovementComponent() : Super()
{
	bCanMove = true;
	MaxWalkSpeedCrouched = 50.f;
	MaxWalkSpeed = 60;
	MaxRunSpeed	 = 100.f;
	MinAnalogWalkSpeed = 0.2f;
	BrakingDecelerationWalking = 30.f;
	MaxStepHeight = 5.f;
	MaxAcceleration = 50.f;
	bUseSeparateBrakingFriction =true;
	
    // base configuration : 
	bOrientRotationToMovement = false; // Character moves in the direction of input...	
	RotationRate = FRotator(0.0f, 50.f, 0.0f); // ...at this rotation rate
	MinTurnInPlaceAngle = 20.f; // we don't need turn in place for less than .. degree
	bUseTurnInPlaceRotationRate = true; // we wnat turn in place
	JumpZVelocity = 600.f; // cats are known to jump high
	AirControl = 0.5f; // cats are very agile
	bIsSitting = false; // we don't start sitting

	// one fix could just be  to set to false:
	bUseFlatBaseForFloorChecks = true;

	bMaintainHorizontalGroundVelocity = false;
}

void UCatMovementComponent::MoveAlongFloor(const FVector& InVelocity, float DeltaSeconds, FStepDownResult* OutStepDownResult)
{
	Super::MoveAlongFloor(InVelocity, DeltaSeconds, OutStepDownResult);
	if(OutStepDownResult != nullptr)
	{
		FloorNormal = OutStepDownResult->FloorResult.HitResult.ImpactNormal;
		// TODO : Check this
		bFloorNormalIsValid = OutStepDownResult->FloorResult.bBlockingHit && !FloorNormal.IsNearlyZero(KINDA_SMALL_NUMBER);
		FindFloorAlignmentNormal(OutStepDownResult->FloorResult.HitResult, FVector(0, 0, -1));
	}

	AdaptToFloorNormal();
}


void UCatMovementComponent::UpdateCharacterStateBeforeMovement(float DeltaSeconds)
{
	Super::UpdateCharacterStateBeforeMovement(DeltaSeconds);
	// Check for a change in sit state. Players toggle sitting by changing bWantsToSit.
	const bool bissitting = IsSitting();
	if (bissitting && (!bWantsToSit || !CanSitInCurrentState()))
	{
		Stand();
	}
	else if (!bissitting && bWantsToSit && CanSitInCurrentState())
	{
		Sit();
	}

	FindFloor(UpdatedComponent->GetComponentLocation(), CurrentFloor, false);
	AdjustFloorHeight();
	SetBaseFromFloor(CurrentFloor);

	if (CurrentFloor.HitResult.IsValidBlockingHit())
	{
		FloorNormal = CurrentFloor.HitResult.ImpactNormal;
		// TODO : Check this
		bFloorNormalIsValid = CurrentFloor.HitResult.bBlockingHit;
		//FloorNormal = FindFloorAlignmentNormal(CurrentFloor.HitResult, FVector(0, 0, -1));
	}
	


}

void UCatMovementComponent::UpdateCharacterStateAfterMovement(float DeltaSeconds)
{
	Super::UpdateCharacterStateAfterMovement(DeltaSeconds);
	// Uncrouch if no longer allowed to be crouched
	if (IsSitting() && !CanCrouchInCurrentState())
	{
		Stand();
	}
	AdaptToFloorNormal();
}

 bool UCatMovementComponent::ApplyRequestedMove(float DeltaTime, float MaxAccel, float MaxSpeed, float Friction, float BrakingDeceleration, FVector& OutAcceleration, float& OutRequestedSpeed)
{
	const bool retval = Super::ApplyRequestedMove(DeltaTime, MaxAccel, MaxSpeed, Friction,  BrakingDeceleration, OutAcceleration, OutRequestedSpeed);
	bIsMoving = retval && OutRequestedSpeed >= MinMovingSpeed;
	return bIsMoving;
}

void UCatMovementComponent::AddInputVector(FVector WorldVector,bool bForce)
{
	if(bCanMove)
	{
		Super::AddInputVector(WorldVector,bForce);
	}
}

float UCatMovementComponent::GetMaxSpeed() const
{
	switch(MovementMode)
	{
	case MOVE_Walking:
	case MOVE_NavWalking:
		return IsCrouching() ? MaxWalkSpeedCrouched : bIsRunning ? MaxRunSpeed : MaxWalkSpeed;
	case MOVE_Falling:
	case MOVE_Swimming:
	case MOVE_Flying:
	case MOVE_Custom:
	case MOVE_None:
	default:
		return Super::GetMaxSpeed();
	}
}


void UCatMovementComponent::FindFloor(const FVector& CapsuleLocation, FFindFloorResult& OutFloorResult, bool bCanUseCachedLocation, const FHitResult* DownwardSweepResult) const
{
	if (!HasValidData() || !UpdatedComponent->IsQueryCollisionEnabled())
	{
		return Super::FindFloor(CapsuleLocation, OutFloorResult, bCanUseCachedLocation, DownwardSweepResult);
	}

	auto CatCapsule = Cast<UCatCapsuleComponent>(CharacterOwner->GetCapsuleComponent());
	if (!CatCapsule
		|| (DownwardSweepResult != NULL && DownwardSweepResult->IsValidBlockingHit())
		|| CatCapsule->Rotation == FRotator::ZeroRotator)
	{
		return Super::FindFloor(CapsuleLocation, OutFloorResult, bCanUseCachedLocation, DownwardSweepResult);
	}

	const float length = CatCapsule->GetRealExtendVector().Z;
	const float radius = CatCapsule->GetRealExtendVector().Y;
	
	ComputeFloorDist(CapsuleLocation, length, length, OutFloorResult, radius, DownwardSweepResult);
}


bool UCatMovementComponent::IsValidLandingSpot(const FVector& CapsuleLocation, const FHitResult& Hit) const
{
	if (!Hit.bBlockingHit)
	{
		return false;
	}

	// Skip some checks if penetrating. Penetration will be handled by the FindFloor call (using a smaller capsule)
	if (!Hit.bStartPenetrating)
	{
		// Reject unwalkable floor normals.
		if (!IsWalkable(Hit))
		{
			return false;
		}

	
		const auto CatCapsule = Cast<UCatCapsuleComponent>(CharacterOwner->GetCapsuleComponent());
		if (!CatCapsule)
			return false;
		const float PawnRadius		= CatCapsule->GetRealExtendVector().X;
		const float PawnHalfHeight	= CatCapsule->GetRealExtendVector().Z;

		// Reject hits that are above our lower hemisphere (can happen when sliding down a vertical surface).
		const float LowerHemisphereZ = Hit.Location.Z - PawnHalfHeight + PawnRadius;
		if (Hit.ImpactPoint.Z >= LowerHemisphereZ)
		{
			return false;
		}

		// Reject hits that are barely on the cusp of the radius of the capsule
		if (!IsWithinEdgeTolerance(Hit.Location, Hit.ImpactPoint, PawnRadius + PawnRadius * ShrinkScale))
		{
			return false;
		}
	}
	else
	{
		// Penetrating
		if (Hit.Normal.Z < KINDA_SMALL_NUMBER)
		{
			// Normal is nearly horizontal or downward, that's a penetration adjustment next to a vertical or overhanging wall. Don't pop to the floor.
			return false;
		}
	}

	FFindFloorResult FloorResult;
	FindFloor(CapsuleLocation, FloorResult, false, &Hit);

	if (!FloorResult.IsWalkableFloor())
	{
		return false;
	}

	return true;
}


void UCatMovementComponent::ComputeFloorDist(const FVector& CapsuleLocation, float LineDistance, float SweepDistance, FFindFloorResult& OutFloorResult, float SweepRadius, const FHitResult* DownwardSweepResult) const
{

	UE_LOG(LogCharacterMovement, VeryVerbose, TEXT("[Role:%d] ComputeFloorDist: %s at location %s"), (int32)CharacterOwner->GetLocalRole(), *GetNameSafe(CharacterOwner), *CapsuleLocation.ToString());
	OutFloorResult.Clear();


	auto CatCapsule = Cast<UCatCapsuleComponent>(CharacterOwner->GetCapsuleComponent());
	if (!CatCapsule 
		|| (DownwardSweepResult != NULL && DownwardSweepResult->IsValidBlockingHit()) 
		|| CatCapsule->Rotation == FRotator::ZeroRotator)
	{
		Super::ComputeFloorDist(CapsuleLocation, LineDistance, SweepDistance, OutFloorResult, SweepRadius, DownwardSweepResult);
		return;
	}
	const FVector Extend = CatCapsule->GetRealExtendVector();
	float PawnHalfHeight = Extend.Z;
	float PawnRadius	 = Extend.X;
	const auto CapsuleTransform = FTransform(CatCapsule->Rotation, CapsuleLocation, CatCapsule->GetComponentScale());

 	bool bSkipSweep = false;
	// We require the sweep distance to be >= the line distance, otherwise the HitResult can't be interpreted as the sweep result.
	if (SweepDistance < LineDistance)
	{
		ensure(SweepDistance >= LineDistance);
		return;
	}

	bool bBlockingHit = false;
	FCollisionQueryParams QueryParams(SCENE_QUERY_STAT(ComputeFloorDist), false, CharacterOwner);
	FCollisionResponseParams ResponseParam;
	InitCollisionParams(QueryParams, ResponseParam);
	const ECollisionChannel CollisionChannel = UpdatedComponent->GetCollisionObjectType();

	// Sweep test
	if (!bSkipSweep && SweepDistance > 0.f && SweepRadius > 0.f)
	{
		// Use a shorter height to avoid sweeps giving weird results if we start on a surface.
		// This also allows us to adjust out of penetrations.
		float ShrinkHeight = (PawnHalfHeight - PawnRadius) * (1.f - ShrinkScale);
		float TraceDist = SweepDistance + ShrinkHeight;
		FCollisionShape CapsuleShape = FCollisionShape::MakeCapsule(SweepRadius, PawnHalfHeight - ShrinkHeight);

		FHitResult Hit(1.f);
		bBlockingHit = CustomFloorSweepTest(Hit, CapsuleTransform, CatCapsule, TraceDist, CollisionChannel, CapsuleShape, QueryParams, ResponseParam);

		if (bBlockingHit)
		{
			// Reject hits adjacent to us, we only care about hits on the bottom portion of our capsule.
			// Check 2D distance to impact point, reject if within a tolerance from radius.
			if (Hit.bStartPenetrating || !IsWithinEdgeTolerance(CapsuleLocation, Hit.ImpactPoint, CapsuleShape.Capsule.Radius * (1 + ShrinkScale)))
			{
				// Use a capsule with a slightly smaller radius and shorter height to avoid the adjacent object.
				// Capsule must not be nearly zero or the trace will fall back to a line trace from the start point and have the wrong length.
				CapsuleShape.Capsule.Radius = FMath::Max(0.f, CapsuleShape.Capsule.Radius - SWEEP_EDGE_REJECT_DISTANCE - KINDA_SMALL_NUMBER);
				if (!CapsuleShape.IsNearlyZero())
				{
					ShrinkHeight = (PawnHalfHeight - PawnRadius) * (1.f - ShrinkScaleOverlap);
					TraceDist = SweepDistance + ShrinkHeight;
					CapsuleShape.Capsule.HalfHeight = FMath::Max(PawnHalfHeight - ShrinkHeight, CapsuleShape.Capsule.Radius);
					Hit.Reset(1.f, false);

					bBlockingHit = CustomFloorSweepTest(Hit, CapsuleTransform, CatCapsule, TraceDist, CollisionChannel, CapsuleShape, QueryParams, ResponseParam);
				}
			}

			// Reduce hit distance by ShrinkHeight because we shrank the capsule for the trace.
			// We allow negative distances here, because this allows us to pull out of penetrations.
			const float MaxPenetrationAdjust = FMath::Max(MAX_FLOOR_DIST, PawnRadius);
			const float SweepResult = FMath::Max(-MaxPenetrationAdjust, Hit.Time * TraceDist - ShrinkHeight);

			OutFloorResult.SetFromSweep(Hit, SweepResult, IsWalkable(Hit) ? false : false);
			if (Hit.IsValidBlockingHit() && IsWalkable(Hit))
			{
				if (SweepResult <= SweepDistance)
				{
					// Hit within test distance.
					OutFloorResult.bWalkableFloor = true;
					return;
				}
			}
		}
	}

	// Since we require a longer sweep than line trace, we don't want to run the line trace if the sweep missed everything.
	// We do however want to try a line trace if the sweep was stuck in penetration.
	if (!OutFloorResult.bBlockingHit && !OutFloorResult.HitResult.bStartPenetrating)
	{
		OutFloorResult.FloorDist = SweepDistance ;
		return;
	}

	// Line trace
	if (LineDistance > 0.f)
	{
		const float ShrinkHeight = PawnHalfHeight;
		const FVector LineTraceStart = CapsuleLocation;
		const float TraceDist = LineDistance + ShrinkHeight;
		const FVector Down = FVector(0.f, 0.f, -TraceDist);
		QueryParams.TraceTag = SCENE_QUERY_STAT_NAME_ONLY(FloorLineTrace);

		FHitResult Hit(1.f);
		bBlockingHit = GetWorld()->LineTraceSingleByChannel(Hit, LineTraceStart, LineTraceStart + Down, CollisionChannel, QueryParams, ResponseParam);

		if (bBlockingHit)
		{
			if (Hit.Time > 0.f)
			{
				// Reduce hit distance by ShrinkHeight because we started the trace higher than the base.
				// We allow negative distances here, because this allows us to pull out of penetrations.
				const float MaxPenetrationAdjust = FMath::Max(MAX_FLOOR_DIST, PawnRadius);
				const float LineResult = FMath::Max(-MaxPenetrationAdjust, Hit.Time * TraceDist - ShrinkHeight);

				OutFloorResult.bBlockingHit = true;
				if (LineResult <= LineDistance && IsWalkable(Hit))
				{
					OutFloorResult.SetFromLineTrace(Hit, OutFloorResult.FloorDist, LineResult, true);
					return;
				}
			}
		}
	}

	// No hits were acceptable.
	OutFloorResult.bWalkableFloor = false;
	OutFloorResult.FloorDist = SweepDistance;
}


bool UCatMovementComponent::CustomFloorSweepTest( FHitResult& OutHit, FTransform capsuleTransform, UCapsuleComponent * capsule, float traceLength, ECollisionChannel TraceChannel,	const struct FCollisionShape& CollisionShape,	const struct FCollisionQueryParams& Params,	const struct FCollisionResponseParams& ResponseParam) const
{
	const FRotator orientation	= capsuleTransform.Rotator();
	const FVector start = capsuleTransform.GetLocation();
	const FVector gravity = FVector::DownVector;
	bool bBlockingHit = false;
	
	if (!capsule || !bUseFlatBaseForFloorChecks || orientation == FRotator::ZeroRotator)
	{
		return Super::FloorSweepTest(OutHit, start, start + gravity * traceLength, TraceChannel, CollisionShape, Params, ResponseParam);
	}
	
	const float CapsuleRadius = CollisionShape.GetCapsuleRadius();
	const float CapsuleHeight = CollisionShape.GetCapsuleHalfHeight();

	auto SweepTest = [&](const FVector A)->bool {
		const auto B = A + (gravity * traceLength);
		// Test with a box that is enclosed by the capsule.
		const FCollisionShape BoxShape = FCollisionShape::MakeBox(FVector(CapsuleRadius * 0.707f, CapsuleRadius * 0.707f, CapsuleHeight));
		// First test with the box rotated so the corners are along the major axes (ie rotated 45 degrees).
		bool retval = GetWorld()->SweepSingleByChannel(OutHit, A, B, FQuat(gravity, PI * 0.25f), TraceChannel, BoxShape, Params, ResponseParam);
		
		if (retval)
		{
			// Test again with the same box, not rotated.
			OutHit.Reset(1.f, false);
			retval = GetWorld()->SweepSingleByChannel(OutHit, A, B, FQuat::Identity, TraceChannel, BoxShape, Params, ResponseParam);
		}
		
#if !UE_BUILD_SHIPPING && WITH_EDITORONLY_DATA
		if (bDebug)
		{
			//DrawDebugBox(GetWorld(), A, BoxShape.GetExtent(), FColor::Orange, true, 0.1, 0, 1);
			DrawDebugBox(GetWorld(), B, BoxShape.GetExtent(), retval ? FColor::Green : FColor::Red, false, 0.05, 0, 1);
		}
#endif
		return retval;
	};
	
	const auto cat = Cast<UCatCapsuleComponent>(capsule);
	const FTransform cattrans = cat->GetOwner() ? cat->GetOwner()->GetActorTransform() : FTransform();
	
	bBlockingHit = SweepTest(cattrans.TransformPosition(cat->GetLocalBottomLocation())) || SweepTest( cattrans.TransformPosition(cat->GetLocalTopLocation()));

	// Ultimate safety, try it the hard way
	if(!bBlockingHit)
		bBlockingHit = GetWorld()->SweepSingleByChannel(OutHit, start, start + gravity * traceLength, FQuat::Identity, TraceChannel, CollisionShape, Params, ResponseParam);
	
	return bBlockingHit;
}

void UCatMovementComponent::PhysicsRotation(float DeltaTime)
{
	// Adapt to floor : 
	AdaptToFloorNormal();

	// Now we want to enable turn in place :
	// the principle is to use an anim to play to rotate what the root motion did not do.
	// So we just check if we can rotate or if we need to wait for turn in place to occur : 
	if (!bUseTurnInPlaceRotationRate || !bIsInTurnInPlaceAnimation)
		return Super::PhysicsRotation(DeltaTime);
}


bool UCatMovementComponent::ShouldRemainVertical() const
{
	// Super does this :
	// return IsMovingOnGround() || IsFalling();
	return false;
}

FVector UCatMovementComponent::ComputeGroundMovementDelta(const FVector& Delta, const FHitResult& RampHit, const bool bHitFromLineTrace) const
{
	const FVector gravity = FVector(0, 0, -1);
	const FVector retval		= Super::ComputeGroundMovementDelta(Delta, RampHit, bHitFromLineTrace);
	const FVector floor_normal   = RampHit.ImpactNormal;
	const FVector contact_normal = RampHit.Normal;

	// TODO: we must adapt our speed to the floor direction  : 

	return retval;


	
}

FVector UCatMovementComponent::FindFloorAlignmentNormal(const FHitResult& RampHit, const FVector& gravity) const 
{
	const float distance = RampHit.bBlockingHit ? RampHit.Distance * 2 : 100;
	// TODO: we must adapt our alignment to the floor direction  :
	const auto cat_capsule = Cast<UCatCapsuleComponent>(UpdatedComponent);
	if (cat_capsule)
	{
		AActor * cat = cat_capsule->GetOwner();
		FVector  cat_normal = FVector(0, 0, 1);
		if (bAlignToSurfaceWithTrace)
		{
			FCollisionQueryParams QueryParams(SCENE_QUERY_STAT(StepUp), false, CharacterOwner);
			FCollisionResponseParams ResponseParam;
			InitCollisionParams(QueryParams, ResponseParam);
			const ECollisionChannel TraceChannel = UpdatedComponent->GetCollisionObjectType();

			auto find_normal = [&TraceChannel, &ResponseParam, &QueryParams, &gravity](UWorld *world, FVector start, float length, bool &IsValid) -> FVector {
				FHitResult OutHit;
				if (world)
					world->LineTraceSingleByChannel(OutHit, start, start + gravity * length, TraceChannel, QueryParams, ResponseParam);
				IsValid = OutHit.IsValidBlockingHit();
				return OutHit.Normal;
			};
			const FTransform cat_trans = cat_capsule->GetOwner() ? cat_capsule->GetOwner()->GetActorTransform() : FTransform();
			bool valid_front, valid_rear;
			const FVector cat_rear = find_normal(GetWorld(), cat_trans.TransformPosition(cat_capsule->GetLocalBottomLocation()), distance, valid_rear);
			const FVector cat_front = find_normal(GetWorld(), cat_trans.TransformPosition(cat_capsule->GetLocalTopLocation()), distance, valid_front);
			cat_normal = (cat_front + cat_rear) / 2;
			bFloorNormalIsValid = valid_front && valid_rear;
		}
		else
		{
			bFloorNormalIsValid = RampHit.IsValidBlockingHit();
			cat_normal = RampHit.ImpactNormal;
		}
#if !UE_BUILD_SHIPPING && WITH_EDITORONLY_DATA
		if (bDebug)
		{
			DrawDebugDirectionalArrow(GetWorld(), cat->GetActorLocation(), cat->GetActorLocation() + cat_normal, 10, FColor::Cyan, false, 0.2, 0, 2);
		}
#endif
		return cat_normal;

	}
	return FVector(0,0,1);
}



bool UCatMovementComponent::IsSitting() const
{
	return bIsSitting;
}

void UCatMovementComponent::RequestSit(bool bNewSit)
{
	bWantsToSit = bNewSit;
}

void UCatMovementComponent::RequestRun(bool bNewRun)
{
	bIsRunning = CanRunInCurrentState() && bNewRun;
}

bool UCatMovementComponent::CanPlayTurnInPlace() const
{
	if (!GetCharacterOwner())
		return false;

	if(IsSitting())
		return false;
	
	if (GetCharacterOwner()->GetVelocity().Size() > MaxTurnInPlaceSpeed)
		return false;
	const FRotator CurrentRotation = UpdatedComponent->GetComponentRotation();
	const FRotator DesiredRotation = GetTurnInPlaceRotation();

	if ((DesiredRotation.Vector() | CurrentRotation.Vector()) <= FMath::Cos(MinTurnInPlaceAngle))
		return true;

	return false;
}

FRotator UCatMovementComponent::GetTurnInPlaceRotation() const
{
	FRotator DesiredRotation = FRotator::ZeroRotator;
	FRotator CharacterRotation = FRotator::ZeroRotator;
	if (GetCharacterOwner() && GetCharacterOwner()->Controller)
	{
		DesiredRotation = GetCharacterOwner()->Controller->GetControlRotation();
		CharacterRotation = UpdatedComponent->GetComponentRotation();
	}
	else
	{
		return DesiredRotation;
	}

	if (ShouldRemainVertical())
	{
		DesiredRotation.Pitch = 0.f;
		DesiredRotation.Yaw = FRotator::NormalizeAxis(DesiredRotation.Yaw);
		DesiredRotation.Roll = 0.f;
		CharacterRotation.Pitch = 0.f;
		CharacterRotation.Yaw = FRotator::NormalizeAxis(CharacterRotation.Yaw);
		CharacterRotation.Roll = 0.f;
	}
	else
	{
		DesiredRotation.Normalize();
		CharacterRotation.Normalize();
	}
	
	return CharacterRotation - DesiredRotation;
}

void UCatMovementComponent::SetIsInTurnInPlaceAnim(bool bIsInAnim)
{
	bIsInTurnInPlaceAnimation = bIsInAnim;
	
}

void UCatMovementComponent::Sit()
{
	if(!bIsSitting)
	{
		bIsSitting = true;
	}
}

void UCatMovementComponent::Stand()
{
	if(bIsSitting)
	{
		bIsSitting = false;
	}
}

bool UCatMovementComponent::AdaptToFloorNormal()
{
	// Align Character to floor :
	float threshold = KINDA_SMALL_NUMBER;
	if (!GetCharacterOwner() || GetCharacterOwner()->IsPendingKillOrUnreachable())
		return false;

	if (bFloorNormalIsValid &&
		(MovementMode == MOVE_Walking || MovementMode == MOVE_NavWalking))
	{
		const FVector forward = GetCharacterOwner()->GetActorForwardVector();
		const FVector orient = FVector::VectorPlaneProject(forward, !FloorNormal.IsNearlyZero(threshold) ? FloorNormal : FVector(0.f, 0.f, 1.f));
		return MoveUpdatedComponent(FVector::ZeroVector, orient.Rotation(), /*bSweep*/ false);
	}
	return false;
}

bool UCatMovementComponent::CanSitInCurrentState() const
{
	if (!CanEverSit())
	{
		return false;
	}

	return (IsFalling() || IsMovingOnGround()) && UpdatedComponent && !UpdatedComponent->IsSimulatingPhysics();
}

bool UCatMovementComponent::CanRunInCurrentState() const
{
	return (IsFalling() || IsMovingOnGround()) && UpdatedComponent && !UpdatedComponent->IsSimulatingPhysics();
}
