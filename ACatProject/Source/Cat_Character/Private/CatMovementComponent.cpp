// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved


#include "CatMovementComponent.h"
#include "CatPawn.h"
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


}

void UCatMovementComponent::PostLoad()
{
	Super::PostLoad();
	CatOwner = Cast<ACatPawn>(GetOwner());
}

ACatPawn* UCatMovementComponent::GetCatOwner() const
{
	return CatOwner;
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
	/*switch(MovementMode)
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
	*/
	return Super::GetMaxSpeed();
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

bool UCatMovementComponent::AdaptToFloorNormal(float deltaTime/*=-1.f*/, bool sweep /*=false*/)
{
	// Align Character to floor :
	float threshold = KINDA_SMALL_NUMBER;
	if (!GetCatOwner() || GetCatOwner()->IsPendingKillOrUnreachable())
		return false;

	if (bFloorNormalIsValid)
		//(MovementMode == MOVE_Walking || MovementMode == MOVE_NavWalking))
	{
		const FVector forward = GetCatOwner()->GetActorForwardVector();
		const FVector orient = FVector::VectorPlaneProject(forward, !FloorNormal.IsNearlyZero(threshold) ? FloorNormal : FVector(0.f, 0.f, 1.f));
		if(deltaTime > 0)
		{
			const auto Rotation = FMath::Lerp(forward, orient, 1/* Align to floor speed here */ * deltaTime).Rotation();
			return MoveUpdatedComponent(FVector::ZeroVector, Rotation, sweep);
		}
		else
		{
			return MoveUpdatedComponent(FVector::ZeroVector, orient.Rotation(), sweep);
		}	
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
