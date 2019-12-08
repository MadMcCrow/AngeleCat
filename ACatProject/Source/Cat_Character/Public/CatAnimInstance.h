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

public:

	UFUNCTION(BlueprintPure, Category = "Speed")
	FORCEINLINE FVector GetVelocity() const {return Velocity; }

	UFUNCTION(BlueprintPure, Category = "Speed")
	FORCEINLINE float GetSpeed() const {return GetVelocity().Size();}

	UFUNCTION(BlueprintPure, Category = "Owner")
	ACatPawn * TryGetOwningCat(bool &isValid) const;

	ACatPawn * TryGetOwningCat() const;


private:

	UPROPERTY()
	FVector Velocity;

	UPROPERTY()
	bool bIsCrouching;

	UPROPERTY()
	bool bIsJumping;

	
};
