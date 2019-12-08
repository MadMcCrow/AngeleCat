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

	/** Base Character rotation rate, in deg/sec. only applies in yaw */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inputs")
	float BaseRotationRate;

private:
	
};
