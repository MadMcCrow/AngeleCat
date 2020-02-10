// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#include "CatPawn.h"
#include "CatMovementComponent.h"
#include "Cat_CharacterPCH.h"


FName ACatPawn::CatMovementComponentName = TEXT("CatMovementComp");

// Sets default values
ACatPawn::ACatPawn(const FObjectInitializer& ObjectInitializer) :
Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false; // need for tick

	CatMovementComp = ObjectInitializer.CreateDefaultSubobject<UCatMovementComponent>(this, CatMovementComponentName);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Movement component sets itself !

	// Don't rotate when the controller rotates. Let that just affect the camera and adapt cat to the orientation via animation
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// our running toggle variable
	bIsRunning = false;


}

void ACatPawn::MoveForward(float inValue)
{
	if(GetCatMovementComponent())
		GetCatMovementComponent()->AddInputVector( GetActorForwardVector() * inValue, false);
}

void ACatPawn::MoveRight(float inValue)
{
	// A Cat does not strafe but turn.
}

 void ACatPawn::Run()
 {
	 bIsRunning = true;
	 //if(GetCatMovementComponent())
	 //	GetCatMovementComponent()->RequestRun(bIsRunning);
 }

  void ACatPawn::StopRunning()
 {
	 bIsRunning = false;
	 //if(GetCatMovementComponent())
	 //	GetCatMovementComponent()->RequestRun(bIsRunning);
 }


void ACatPawn::ToggleCrouch()
{
	bIsCrouching = !bIsCrouching;
	//if(GetCatMovementComponent())
	//	GetCatMovementComponent()->bWantsToCrouch = bIsCrouching;
}

UCatMovementComponent * ACatPawn::GetCatMovementComponent() const
{
	return CatMovementComp;
}

