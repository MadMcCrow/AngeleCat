// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#include "CatPawn.h"
#include "CatMovementComponent.h"
#include "Cat_CharacterPCH.h"


// Sets default values
ACatPawn::ACatPawn(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UCatMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = false; // need for tick

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Movement component sets itself !

	// Don't rotate when the controller rotates. Let that just affect the camera and adapt cat to the orientation via animation
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

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


