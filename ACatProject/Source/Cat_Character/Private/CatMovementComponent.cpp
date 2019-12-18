// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved


#include "CatMovementComponent.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "CatCapsuleComponent.h"
//#include "EngineStats.h"
//#include "Net/PerfCountersHelpers.h"

#if !UE_BUILD_SHIPPING
#include "DrawDebugHelpers.h"
#endif

// TODO : may not be a good think to just copy the define/declares
DEFINE_LOG_CATEGORY_STATIC(LogCharacterMovement, Log, All);
//DECLARE_CYCLE_STAT(TEXT("Char FindFloor"), STAT_CharFindFloor, STATGROUP_Character);


float UCatMovementComponent::MinMovingSpeed = KINDA_SMALL_NUMBER;

UCatMovementComponent::UCatMovementComponent() : Super()
{
	bCanMove = true;
	BaseRotationRate = 450.f;
	MaxWalkSpeedCrouched = 50.f;
	MaxWalkSpeed = 60;
	MaxRunSpeed	 = 100.f;
	MinAnalogWalkSpeed = 0.2f;
	BrakingDecelerationWalking = 30.f;
	MaxStepHeight = 12.f;
	MaxAcceleration = 50.f;
	bUseSeparateBrakingFriction =true;
	
    // base configuration : 
	bOrientRotationToMovement = true; // Character moves in the direction of input...	
	RotationRate = FRotator(0.0f, BaseRotationRate, 0.0f); // ...at this rotation rate
	JumpZVelocity = 600.f; // cats are known to jump high
	AirControl = 0.5f; // cats are very agile
	bIsSitting = false; // we don't start sitting

	// one fix could just be  to set to false:
	bUseFlatBaseForFloorChecks = true;
}

void UCatMovementComponent::MoveAlongFloor(const FVector& InVelocity, float DeltaSeconds, FStepDownResult* OutStepDownResult)
{
	Super::MoveAlongFloor(InVelocity, DeltaSeconds, OutStepDownResult);
	if(OutStepDownResult != nullptr)
	{
		FloorNormal = OutStepDownResult->FloorResult.HitResult.ImpactNormal;
		// TODO : Check this
		bFloorNormalIsValid = OutStepDownResult->FloorResult.bBlockingHit;
	}
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
}

void UCatMovementComponent::UpdateCharacterStateAfterMovement(float DeltaSeconds)
{
	Super::UpdateCharacterStateAfterMovement(DeltaSeconds);
	// Uncrouch if no longer allowed to be crouched
	if (IsSitting() && !CanCrouchInCurrentState())
	{
		Stand();
	}
}

 bool UCatMovementComponent::ApplyRequestedMove(float DeltaTime, float MaxAccel, float MaxSpeed, float Friction, float BrakingDeceleration, FVector& OutAcceleration, float& OutRequestedSpeed)
{
	bool retval = Super::ApplyRequestedMove(DeltaTime, MaxAccel, MaxSpeed, Friction,  BrakingDeceleration, OutAcceleration, OutRequestedSpeed);
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


void UCatMovementComponent::ComputeFloorDist(const FVector& CapsuleLocation, float LineDistance, float SweepDistance, FFindFloorResult& OutFloorResult, float SweepRadius, const FHitResult* DownwardSweepResult) const
{
	UE_LOG(LogCharacterMovement, VeryVerbose, TEXT("[Role:%d] ComputeFloorDist: %s at location %s"), (int32)CharacterOwner->GetLocalRole(), *GetNameSafe(CharacterOwner), *CapsuleLocation.ToString());
	OutFloorResult.Clear();

	float PawnRadius, PawnHalfHeight;

	auto CatCapsule = Cast<UCatCapsuleComponent>(CharacterOwner->GetCapsuleComponent());
	if (!CatCapsule 
		|| (DownwardSweepResult != NULL && DownwardSweepResult->IsValidBlockingHit()) 
		|| CatCapsule->Rotation == FRotator::ZeroRotator)
	{
		Super::ComputeFloorDist(CapsuleLocation, LineDistance, SweepDistance, OutFloorResult, SweepRadius, DownwardSweepResult);
		return;
	}

	CatCapsule->GetScaledCapsuleSize(PawnRadius, PawnHalfHeight);
	const auto CapsuleTransform = FTransform(CatCapsule->Rotation, CapsuleLocation, CatCapsule->GetComponentScale());
	FVector ZCapsuleHalf = CatCapsule->Rotation.RotateVector(FVector::UpVector * (PawnHalfHeight - PawnRadius)).ProjectOnTo(FVector::UpVector);
	PawnHalfHeight = ZCapsuleHalf.Size() + PawnRadius;

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
		const float ShrinkScale = 0.9f;
		const float ShrinkScaleOverlap = 0.1f;
		float ShrinkHeight = (PawnHalfHeight - PawnRadius) * (1.f - ShrinkScale);
		float TraceDist = SweepDistance + ShrinkHeight;
		FCollisionShape CapsuleShape = FCollisionShape::MakeCapsule(SweepRadius, PawnHalfHeight - ShrinkHeight);

		FHitResult Hit(1.f);
		bBlockingHit = CustomFloorSweepTest(Hit, CapsuleTransform, CatCapsule, TraceDist, CollisionChannel, CapsuleShape, QueryParams, ResponseParam);

		if (bBlockingHit)
		{
			// Reject hits adjacent to us, we only care about hits on the bottom portion of our capsule.
			// Check 2D distance to impact point, reject if within a tolerance from radius.
			if (Hit.bStartPenetrating || !IsWithinEdgeTolerance(CapsuleLocation, Hit.ImpactPoint, CapsuleShape.Capsule.Radius))
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

			OutFloorResult.SetFromSweep(Hit, SweepResult, false);
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
		OutFloorResult.FloorDist = SweepDistance;
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
	FVector start = capsuleTransform.GetLocation();
	const FVector gravity = FVector::DownVector;
	if (!capsule || !bUseFlatBaseForFloorChecks || orientation == FRotator::ZeroRotator)
	{
		return Super::FloorSweepTest(OutHit, start, start + gravity * traceLength, TraceChannel, CollisionShape, Params, ResponseParam);
	}

	bool bBlockingHit = false;
	
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
			DrawDebugBox(GetWorld(), A, BoxShape.GetExtent(), FColor::Orange, true, 0.1, 0, 1);
			DrawDebugBox(GetWorld(), B, BoxShape.GetExtent(), retval ? FColor::Green : FColor::Red, true, 0.2, 0, 1);
		}
#endif
		return retval;
	};
	//TODO :  do front and back test instead of something else.
	const auto cat = Cast<UCatCapsuleComponent>(capsule);
	const FTransform cattrans = cat->GetOwner() ? cat->GetOwner()->GetActorTransform() : FTransform();
	
	bBlockingHit = SweepTest(cattrans.TransformPosition(cat->GetLocalBottomLocation())) || SweepTest( cattrans.TransformPosition(cat->GetLocalTopLocation()));
		
	return bBlockingHit;
}

bool UCatMovementComponent::CanStepUp(const FHitResult& Hit) const
{
	if (!Hit.IsValidBlockingHit() || !HasValidData() || MovementMode == MOVE_Falling)
	{
		return false;
	}

	// No component for "fake" hits when we are on a known good base.
	const UPrimitiveComponent* HitComponent = Hit.Component.Get();
	if (!HitComponent)
	{
		return true;
	}

	if (!HitComponent->CanCharacterStepUp(CharacterOwner))
	{
		return false;
	}

	// No actor for "fake" hits when we are on a known good base.
	const AActor* HitActor = Hit.GetActor();
	if (!HitActor)
	{
		return true;
	}

	if (!HitActor->CanBeBaseForCharacter(CharacterOwner))
	{
		return false;
	}
	return true;
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
