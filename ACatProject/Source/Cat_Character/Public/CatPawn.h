// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CatPawn.generated.h"

class UCatMovementComponent;

UCLASS(ClassGroup = "Cat_Character", Category = "Pawn")
class CAT_CHARACTER_API ACatPawn : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACatPawn(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/**	MoveForward : Add movement input inthe forward axis (X) */
	UFUNCTION(BlueprintCallable, Category = "Movement")
	virtual void MoveForward(float inValue);

	/**	MoveRight : Add movement input in the right axis (Y) */
	UFUNCTION(BlueprintCallable, Category = "Movement")
	virtual void MoveRight(float inValue);

	/**	Run : Set movement to running */
	UFUNCTION(BlueprintCallable, Category = "Movement")
	virtual void Run();

	/**	StopRunning : Set movement to walking */
	UFUNCTION(BlueprintCallable, Category = "Movement")
	virtual void StopRunning();

	/**	ToggleCrouch : Set movement to crouching */
	UFUNCTION(BlueprintCallable, Category = "Movement")
	virtual void ToggleCrouch();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inputs")
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inputs")
	float BaseLookUpRate;

	UFUNCTION(BlueprintPure, Category = "Movement")
	virtual UCatMovementComponent * GetCatMovementComponent() const;

private:

	/**	Variable used for toggling running */
	UPROPERTY(transient)
	bool bIsRunning;

	/**	Variable used for toggling crouching */
	UPROPERTY(transient)
	bool bIsCrouching;

	
};
