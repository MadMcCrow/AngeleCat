// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#pragma once

#include "CatPawn.h"
#include "CatPlayerPawn.generated.h"

// forward declaration
class UCameraComponent;
class USpringArmComponent;
class UInputComponent;

UCLASS(ClassGroup = "Cat_Character", Category = "Pawn")
class CAT_CHARACTER_API ACatPlayerPawn : public ACatPawn
{
	GENERATED_BODY()

public:

	ACatPlayerPawn();

	virtual UInputComponent* CreatePlayerInputComponent() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	static FName SpringArmName;
	static FName CameraCompName;

private:

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

public:

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	UFUNCTION()
	virtual void TurnAtRate(float inRate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	UFUNCTION()
	virtual void LookUpAtRate(float inRate);



public:
	/** Returns CameraBoom subobject **/
	UFUNCTION(BlueprintPure, Category = "Camera")
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	UFUNCTION(BlueprintPure, Category = "Camera")
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }



};
