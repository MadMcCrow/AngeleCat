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

	/** UCharacterMovementComponent interface */
	virtual void MoveAlongFloor(const FVector& InVelocity, float DeltaSeconds, FStepDownResult* OutStepDownResult = nullptr) override;
	virtual void UpdateCharacterStateBeforeMovement(float DeltaSeconds) override;
	virtual void UpdateCharacterStateAfterMovement(float DeltaSeconds) override;
	virtual bool ApplyRequestedMove(float DeltaTime, float MaxAccel, float MaxSpeed, float Friction, float BrakingDeceleration, FVector& OutAcceleration, float& OutRequestedSpeed) override;
	virtual void AddInputVector(FVector WorldVector,bool bForce) override;
	virtual float GetMaxSpeed() const override;
	virtual void ComputeFloorDist(const FVector& CapsuleLocation, float LineDistance, float SweepDistance, FFindFloorResult& OutFloorResult, float SweepRadius, const FHitResult* DownwardSweepResult = nullptr) const override;
	virtual void PhysicsRotation(float DeltaTime) override;
	virtual FVector ComputeGroundMovementDelta(const FVector& Delta, const FHitResult& RampHit, bool bHitFromLineTrace) const override;
	virtual bool ShouldRemainVertical() const override;
	/** ~ UCharacterMovementComponent interface */

	
	// replace FloorSweepTest() from Super.
	virtual bool CustomFloorSweepTest(FHitResult& OutHit, FTransform capsuleTransform, UCapsuleComponent* capsule, float traceLength, ECollisionChannel TraceChannel, const FCollisionShape& CollisionShape, const FCollisionQueryParams& Params, const FCollisionResponseParams& ResponseParam) const;

	// Allows to find the angle we should conform to
	virtual FVector FindFloorAlignmentNormal(const FHitResult& RampHit, const FVector& gravity) const;
	
	/**
	 * Use line trace to find surfaces and align to surface when going up or down
	 */
	UPROPERTY(Category = "Character Movement: Walking", EditAnywhere, BlueprintReadWrite)
	uint8 bAlignToSurfaceWithTrace : 1;

	/**
	 * If true, Will enable turn in place animation. Overrides OrientRotationToMovement and bUseControllerDesiredRotation. 
	 */
	UPROPERTY(Category = "Character Movement (Rotation Settings)", EditAnywhere, BlueprintReadWrite)
	uint8 bUseTurnInPlaceRotationRate : 1;

	/**
	 * If speed is faster than this, we will no apply turn in place
	 */
	UPROPERTY(Category = "Character Movement (Rotation Settings)", EditAnywhere, BlueprintReadWrite)
	float MaxTurnInPlaceSpeed;

	/**
	 * If Rotation angle is bigger than this, we need to turn in place
	 */
	UPROPERTY(Category = "Character Movement (Rotation Settings)", EditAnywhere, BlueprintReadWrite)
	float MinTurnInPlaceAngle;
	
	/**Get current sitting status */
	UFUNCTION(BlueprintPure, Category = "Movement|Sitting")
	virtual bool IsSitting() const;

	UFUNCTION(BlueprintCallable, Category= "Movement|Sitting")
	virtual void RequestSit(bool bNewSit = true);

	UFUNCTION(BlueprintCallable, Category= "Movement|Running")
	virtual void RequestRun(bool bNewRun = true);

	UFUNCTION(BlueprintPure, Category = "Movement|Walking")
	virtual bool CanPlayTurnInPlace() const;

	UFUNCTION(BlueprintPure, Category = "Movement|TurnInPlace")
	virtual FRotator GetTurnInPlaceRotation() const;

	UFUNCTION(BlueprintCallable, Category = "Movement|TurnInPlace")
	virtual void SetIsInTurnInPlaceAnim(bool bIsInAnim);


protected:

#if WITH_EDITORONLY_DATA
	UPROPERTY(Category = "Character Movement: Walking", EditAnywhere, BlueprintReadWrite)
	bool bDebug;
#endif // WITH_EDITORONLY_DATA

	/**	Run speed for this character */
	UPROPERTY(Category="Character Movement: Walking", EditAnywhere, BlueprintReadWrite, meta=(ClampMin="0", UIMin="0"))
	float MaxRunSpeed;

	/**
	 *	Shrink scale ratio used for floor detection (see ComputeFloorDist)
	 */
	UPROPERTY(Category = "Character Movement: Walking", EditDefaultsOnly, AdvancedDisplay, meta =(NoGetter))
	float ShrinkScale = 0.5f;

	/**
	 * Shrink scale ratio used for floor detection (see ComputeFloorDist)
	 */
	UPROPERTY(Category = "Character Movement: Walking", EditDefaultsOnly, AdvancedDisplay, meta = (NoGetter))
	float ShrinkScaleOverlap = 0.5f;

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

private:

	/**	Is Sitting ? */
	UPROPERTY()
	bool bWantsToSit;

	UPROPERTY(transient)
	bool bIsSitting;

	UPROPERTY(transient)
	FVector FloorNormal;

	UPROPERTY(transient)
	FRotator FloorOrient;

	UPROPERTY(transient)
	bool bFloorNormalIsValid;

	UPROPERTY(transient)
	bool bIsMoving;
 
	static float MinMovingSpeed;

	UPROPERTY(transient)
	bool bCanMove;

	UPROPERTY(transient)
	bool bIsRunning;

	UPROPERTY(transient)
	bool bIsInTurnInPlaceAnimation;
};
