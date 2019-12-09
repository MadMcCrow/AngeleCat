// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved


#include "CatMovementComponent.h"

float UCatMovementComponent::MinMovingSpeed = KINDA_SMALL_NUMBER;

UCatMovementComponent::UCatMovementComponent() : Super()
{
	bCanMove = true;
	BaseRotationRate = 450.f;
	MaxWalkSpeedCrouched = 30.f;
	MaxWalkSpeed = 60;
	MaxRunSpeed	 = 100.f;

	MaxAcceleration = 50.f;
	BrakingDecelerationWalking = 0.5;
	bUseSeparateBrakingFriction =true;
	
    // base configuration : 
	bOrientRotationToMovement = true; // Character moves in the direction of input...	
	RotationRate = FRotator(0.0f, BaseRotationRate, 0.0f); // ...at this rotation rate
	JumpZVelocity = 600.f; // cats are known to jump high
	AirControl = 0.5f; // cats are very agile
	bIsSitting = false; // we don't start sitting
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
