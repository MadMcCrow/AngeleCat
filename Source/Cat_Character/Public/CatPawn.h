// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CatPawn.generated.h"

UCLASS(ClassGroup = "Cat_Character", Category = "Pawn")
class CAT_CHARACTER_API ACatPawn : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACatPawn();

	/**	MoveForward : Add movement input inthe forward axis (X) */
	UFUNCTION()
	virtual void MoveForward(float inValue);

	/**	MoveRight : Add movement input in the right axis (Y) */
	UFUNCTION()
	virtual void MoveRight(float inValue);

	
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inputs")
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inputs")
	float BaseLookUpRate;

	/** Base Character rotation rate, in deg/sec. only applies in yaw */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inputs")
	float BaseRotationRate;




};
