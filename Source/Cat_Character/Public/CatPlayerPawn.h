// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#pragma once

#include "CatPawn.h"
#include "CatPlayerPawn.generated.h"

UCLASS(ClassGroup = "Cat_Character", Category = "Pawn")
class CAT_CHARACTER_API ACatPlayerPawn : public ACatPawn
{
	GENERATED_BODY()

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
