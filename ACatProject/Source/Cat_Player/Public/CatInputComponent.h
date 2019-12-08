// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/InputComponent.h"
#include "CatInputComponent.generated.h"

// Forward Declaration
class ACharacter;
class APlayerController;

/**
 * 
 */
UCLASS(ClassGroup = "Cat_Player", Category = "Input")
class CAT_PLAYER_API UCatInputComponent : public UInputComponent
{
	GENERATED_BODY()

public:

	UCatInputComponent(const FObjectInitializer &ObjectInitializer = FObjectInitializer::Get());

	/**	Bind stored input in this component to functions in character	*/
	UFUNCTION()
	virtual void BindInputsToCharacter(ACharacter * characterTarget);

	/**	Bind stored input in this component to functions in controller	*/
	UFUNCTION()
	virtual void BindInputsToController(APlayerController * controller);

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Input Names")
	FName JumpAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input Names")
	FName MoveForwardAxis;

	UPROPERTY(EditDefaultsOnly, Category = "Input Names")
	FName MoveRightAxis;

	UPROPERTY(EditDefaultsOnly, Category = "Input Names")
	FName TurnAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input Names")
	FName TurnRateAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input Names")
	FName LookUpAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input Names")
	FName LookUpRateAction;

};
