// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#include "CatPawn.h"
#include "Cat_CharacterPCH.h"


// Sets default values
ACatPawn::ACatPawn()
{
	PrimaryActorTick.bCanEverTick = false; // need for tick

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
	BaseRotationRate = 450.f;

		// Don't rotate when the controller rotates. Let that just affect the camera and adapt cat to the orientation via animation
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	if(GetCharacterMovement())
	{
		GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
		GetCharacterMovement()->RotationRate = FRotator(0.0f, BaseRotationRate, 0.0f); // ...at this rotation rate
		GetCharacterMovement()->JumpZVelocity = 600.f; // cats are known to jump high
		GetCharacterMovement()->AirControl = 0.5f; // cats are very agile
	}


}

void ACatPawn::MoveForward(float inValue)
{
	if(GetCharacterMovement())
		GetCharacterMovement()->AddInputVector( GetActorForwardVector() * inValue, false);
}

void ACatPawn::MoveRight(float inValue)
{
	if(GetCharacterMovement())
		GetCharacterMovement()->AddInputVector( GetActorRightVector() * inValue, false);
}


