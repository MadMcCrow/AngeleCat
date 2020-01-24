// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "CatCapsuleComponent.generated.h"

/**
 * 
 */
UCLASS()
class CAT_CHARACTER_API UCatCapsuleComponent : public UCapsuleComponent
{
	GENERATED_BODY()

public:

	UCatCapsuleComponent(const FObjectInitializer &ObjectInitializer);

	virtual void UpdateBodySetup() override;
	//virtual struct FCollisionShape GetCollisionShape(float Inflation = 0.0f) const override;

	virtual FPrimitiveSceneProxy* CreateSceneProxy() override;

	void CreateShapeBodySetupIfNeededSphyl();

#if WITH_PHYSX
	void SetShapeToNewGeomSphyl(const FPhysicsShapeHandle& Shape);
#endif // WITH_PHYSX
	
	/** Rotation of the  capsule*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Shape")
	FRotator Rotation;

	FQuat QuatRotation() {return FQuat(Rotation);}

	virtual FTransform GetWorldTransform() const;


	UFUNCTION(BlueprintPure, Category = "Capsule")
	virtual FVector GetLocalTopLocation(bool bIncludeRadius = false) const;

	UFUNCTION(BlueprintPure, Category = "Capsule")
	virtual FVector GetLocalBottomLocation(bool bIncludeRadius = false) const;

	UFUNCTION(BlueprintPure, Category = "Capsule")
	virtual FVector GetWorldTopLocation(bool bIncludeRadius = false) const;

	UFUNCTION(BlueprintPure, Category = "Capsule")
	virtual FVector GetWorldBottomLocation(bool bIncludeRadius = false) const;


};
