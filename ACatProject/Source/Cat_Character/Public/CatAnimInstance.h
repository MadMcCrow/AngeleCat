// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CatAnimInstance.generated.h"


//forward declaration
class ACatPawn;

/**
 * 
 */
UCLASS(ClassGroup = "Cat_Character", Category = "Animation")
class CAT_CHARACTER_API UCatAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public :

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:

	/** Get velocity's vector */
	UFUNCTION(BlueprintPure, Category = "Movement|Speed")
	FORCEINLINE FVector GetVelocity() const {return Velocity; }

	/** Get velocity's vector's length*/
	UFUNCTION(BlueprintPure, Category = "Movement|Speed")
	FORCEINLINE float GetSpeed() const {return GetVelocity().Size();}

	/** Get crouching info stored in this instance */
	UFUNCTION(BlueprintPure, Category = "Movement|Speed")
	FORCEINLINE bool GetIsCrouching() const {return bIsCrouching;}

	/** Get jumping info stored in this instance */
	UFUNCTION(BlueprintPure, Category = "Movement|Speed")
	FORCEINLINE bool GetIsJumping() const {return bIsJumping;}

	/** Get sitting info stored in this instance */
	UFUNCTION(BlueprintPure, Category = "Movement|Speed")
	FORCEINLINE bool GetIsSitting() const {return bIsSitting;}

	/**Try to get owning cat character */
	UFUNCTION(BlueprintPure, Category = "Owner")
	ACatPawn * TryGetOwningCat(bool &isValid) const;
	ACatPawn * TryGetOwningCat() const;

private:

	/**	Skeleton movement speed	weighted direction	*/
	UPROPERTY(transient)
	FVector Velocity;

	/**	Is character crouching	*/
	UPROPERTY(transient)
	bool bIsCrouching;

	/**	Is character jumping	*/
	UPROPERTY(transient)
	bool bIsJumping;

	/**	Is character sitting	*/
	UPROPERTY(transient)
	bool bIsSitting;

	
};
