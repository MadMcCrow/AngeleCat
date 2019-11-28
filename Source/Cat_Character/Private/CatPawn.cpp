// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#include "CatPawn.h"
#include "Cat_CharacterPCH.h"


// Sets default values
ACatPawn::ACatPawn()
{
	PrimaryActorTick.bCanEverTick = false; // need for tick
}

void ACatPawn::MoveForward(float inValue)
{
	if(GetMovementComponent())
		GetMovementComponent()->AddInputVector( GetActorForwardVector() * inValue, false);
}

void ACatPawn::MoveRight(float inValue)
{
	if(GetMovementComponent())
		GetMovementComponent()->AddInputVector( GetActorRightVector() * inValue, false);
}
