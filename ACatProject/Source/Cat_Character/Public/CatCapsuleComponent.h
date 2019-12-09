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
	virtual void UpdateBodySetup() override;
	//virtual struct FCollisionShape GetCollisionShape(float Inflation = 0.0f) const override;

	virtual FPrimitiveSceneProxy* CreateSceneProxy() override;

	void CreateShapeBodySetupIfNeededSphyl();

#if WITH_PHYSX
	void SetShapeToNewGeomSphyl(const FPhysicsShapeHandle& Shape);
#endif // WITH_PHYSX
	
	static const FRotator Rotation;
	static const FQuat QuatRotation() {return FQuat(Rotation);}
};
