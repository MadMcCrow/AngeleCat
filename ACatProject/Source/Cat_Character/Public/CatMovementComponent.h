// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CatMovementComponent.generated.h"


/**
 *  Base Class for Animation blueprints
 */
UCLASS(ClassGroup = "Cat_Character", Category = "Movement")
class CAT_CHARACTER_API UCatMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public :

	UCatMovementComponent();

	virtual void MoveAlongFloor(const FVector& InVelocity, float DeltaSeconds, FStepDownResult* OutStepDownResult = NULL) override;
	virtual void UpdateCharacterStateBeforeMovement(float DeltaSeconds) override;
	virtual void UpdateCharacterStateAfterMovement(float DeltaSeconds) override;
	virtual bool ApplyRequestedMove(float DeltaTime, float MaxAccel, float MaxSpeed, float Friction, float BrakingDeceleration, FVector& OutAcceleration, float& OutRequestedSpeed) override;


	/** Base Character rotation rate, in deg/sec. only applies in yaw */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement|Rotation")
	float BaseRotationRate;

	/**Get current sitting status */
	UFUNCTION(BlueprintPure, Category = "Movement|Sitting")
	virtual bool IsSitting() const;

	UFUNCTION(BlueprintCallable, Category= "Movement|Sitting")
	virtual void RequestSit(bool bNewSit = true);
protected:

	/**	Determine if the cat can sit where he stands */
	UFUNCTION(BlueprintPure, Category = "Movement|Sitting")
	virtual bool CanSitInCurrentState() const;

	UFUNCTION()
	virtual bool CanEverSit() const {return true;}

	/**	Ask the cat to sit/stand. will fail if cannot sit */
	UFUNCTION(BlueprintCallable, Category = "Movement|Sitting")
	virtual void Sit();

	UFUNCTION(BlueprintCallable, Category = "Movement|Sitting")
	virtual void Stand();


private:

	/**	Is Sitting ? */
	UPROPERTY()
	bool bWantsToSit;

	UPROPERTY(transient)
	bool bIsSitting;

	UPROPERTY(transient)
	FVector FloorNormal;

	UPROPERTY(transient)
	bool bFloorNormalIsValid;

	UPROPERTY(transient)
	bool bIsMoving;
 
	static float MinMovingSpeed;
};
