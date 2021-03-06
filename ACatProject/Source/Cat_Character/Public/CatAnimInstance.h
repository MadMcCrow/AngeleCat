// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CatAnimInstance.generated.h"


//forward declaration
class ACatPawn;

/**
 * 	Base Class for cat animations bluprints. provide helpers for state machines
 */
UCLASS(ClassGroup = "Cat_Character", Category = "Animation")
class CAT_CHARACTER_API UCatAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public :

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:

	/** Get velocity's vector */
	UFUNCTION(BlueprintPure, Category = "Movement|Speed", meta = (BlueprintThreadSafe))
	FORCEINLINE FVector GetVelocity() const {return Velocity; }

	/** Get velocity's vector's length*/
	UFUNCTION(BlueprintPure, Category = "Movement|Speed", meta = (BlueprintThreadSafe))
	FORCEINLINE float GetSpeed() const {return GetVelocity().Size();}

	/** Get Direction's vector */
	UFUNCTION(BlueprintPure, Category = "Movement|Direction", meta = (BlueprintThreadSafe))
	FORCEINLINE FVector GetDirection() const { return Direction; }

	/** Get Direction's vector */
	UFUNCTION(BlueprintPure, Category = "Movement|Direction", meta = (BlueprintThreadSafe))
	FORCEINLINE FVector GetInputDirection() const { return InputDirection; }
	
	/** Get velocity's vector */
	UFUNCTION(BlueprintPure, Category = "Movement|Direction", meta = (BlueprintThreadSafe))
	FORCEINLINE float GetDirectionDotVelocity() const { return GetDirection() | GetVelocity(); }

	/** Get velocity's vector */
	UFUNCTION(BlueprintPure, Category = "Movement|Direction", meta = (BlueprintThreadSafe))
	FORCEINLINE float GetInputDotVelocity() const { return GetInputDirection() | GetVelocity(); }

	/** Get velocity's vector's length*/
	UFUNCTION(BlueprintPure, Category = "Movement|State Machine", meta = (BlueprintThreadSafe))
	FORCEINLINE bool IsMoving() const {return GetVelocity().Size() >= MinWalkSpeed;}

	/** Get crouching info stored in this instance */
	UFUNCTION(BlueprintPure,Category = "Movement|State Machine", meta = (BlueprintThreadSafe))
	FORCEINLINE bool IsCrouching() const {return bIsCrouching;}

	/** Get jumping info stored in this instance */
	UFUNCTION(BlueprintPure, Category = "Movement|State Machine", meta = (BlueprintThreadSafe))
	FORCEINLINE bool IsJumping() const {return bIsJumping;}

	/** Get sitting info stored in this instance */
	UFUNCTION(BlueprintPure, Category = "Movement|State Machine", meta = (BlueprintThreadSafe))
	FORCEINLINE bool IsSitting() const {return bIsSitting;}

	/** Get sitting  and crouching info stored in this instance */
	UFUNCTION(BlueprintPure, Category = "Movement|State Machine", meta = (BlueprintThreadSafe))
	FORCEINLINE bool IsStanding() const {return !bIsSitting && !bIsCrouching;}

	/** Get sitting  and crouching info stored in this instance */
	UFUNCTION(BlueprintPure, Category = "Movement|TurnInPlace", meta = (BlueprintThreadSafe))
	FORCEINLINE bool IsTurnInPlace() const { return bIsInTurnInPlace; }

	/** Get sitting  and crouching info stored in this instance */
	UFUNCTION(BlueprintPure, Category = "Movement|TurnInPlace", meta = (BlueprintThreadSafe))
	FORCEINLINE float GetTurnInPlaceAngle() const { return TurnInPlaceAngle; }

	/**Try to get owning cat character */
	UFUNCTION(BlueprintPure, Category = "Owner")
	ACatPawn * TryGetOwningCat(bool &isValid) const;
	ACatPawn * TryGetOwningCat() const;

private:

	/**	Skeleton movement speed	weighted direction in world space */
	UPROPERTY(transient)
	FVector Velocity;

	/**	Actor direction in world space	*/
	UPROPERTY(transient)
	FVector Direction;

	/**	Aiming Direction in world space	*/
	UPROPERTY(transient)
	FVector InputDirection;

	/**	Is character crouching	*/
	UPROPERTY(transient)
	bool bIsCrouching;

	/**	Is character jumping	*/
	UPROPERTY(transient)
	bool bIsJumping;

	/**	Is character sitting	*/
	UPROPERTY(transient)
	bool bIsSitting;

	/**	Is character doing turn in place	*/
	UPROPERTY(transient)
	bool bIsInTurnInPlace;

	/**	Actor direction in world space	*/
	UPROPERTY(transient)
	float TurnInPlaceAngle;

	/**	minimum speed to take into consideration	*/
	static float MinWalkSpeed;
	
};
