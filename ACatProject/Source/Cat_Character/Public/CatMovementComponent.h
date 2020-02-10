// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CatMovementComponent.generated.h"


/**
 *  Base Class for Animation blueprints
 */
UCLASS(ClassGroup = "Cat_Character", Category = "Movement")
class CAT_CHARACTER_API UCatMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()

	friend class ACatPawn;

public :

	UCatMovementComponent();
	virtual void PostLoad() override;
	void AddInputVector(FVector WorldVector, bool bForce) override;
	float GetMaxSpeed() const override;

	UFUNCTION(BlueprintPure, meta=(HideSelfPin))
	ACatPawn* GetCatOwner() const;


protected:



#if WITH_EDITORONLY_DATA
	UPROPERTY(Category = "Movement|Walking", EditAnywhere, BlueprintReadWrite)
	bool bDebug;
#endif // WITH_EDITORONLY_DATA


	/**	Determine if the cat can sit where he stands */
	UFUNCTION(BlueprintPure, Category = "Movement|Sitting")
	virtual bool CanSitInCurrentState() const;

	/**	Determine if the cat can sit where he stands */
	UFUNCTION(BlueprintPure, Category = "Movement|Running")
	virtual bool CanRunInCurrentState() const;

	UFUNCTION()
	virtual bool CanEverSit() const {return true;}

	/**	Ask the cat to sit/stand. will fail if cannot sit */
	UFUNCTION(BlueprintCallable, Category = "Movement|Sitting")
	virtual void Sit();

	UFUNCTION(BlueprintCallable, Category = "Movement|Sitting")
	virtual void Stand();

	/**
	 *	Adapt to the floor beneath
	 *	@see FloorNormal 
	*/
	UFUNCTION(BlueprintCallable, Category = "Movement|Walking")
	virtual bool AdaptToFloorNormal(float deltaTime = -1.f, bool sweep = false);

private:

	/**	Is Sitting ? */
	UPROPERTY()
	bool bWantsToSit;

	UPROPERTY(transient)
	bool bIsSitting;

	UPROPERTY(transient)
	FVector FloorNormal;

	UPROPERTY(transient)
	mutable bool bFloorNormalIsValid;

	UPROPERTY(transient)
	bool bIsMoving;
 
	static float MinMovingSpeed;

	UPROPERTY(transient)
	bool bCanMove;

	UPROPERTY(transient)
	bool bIsRunning;

	UPROPERTY(transient)
	bool bIsInTurnInPlaceAnimation;

	/** Cat movement component belongs to */
	UPROPERTY(Transient, DuplicateTransient)
	ACatPawn* CatOwner;
};
