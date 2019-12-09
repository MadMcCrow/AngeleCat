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

	UPROPERTY(EditDefaultsOnly, Category = "Input Names|Actions")
	FName JumpAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input Names|Actions")
	FName RunAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input Names|Actions")
	FName CrouchAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input Names|Axis")
	FName MoveForwardAxis;

	UPROPERTY(EditDefaultsOnly, Category = "Input Names|Axis")
	FName MoveRightAxis;

	UPROPERTY(EditDefaultsOnly, Category = "Input Names|Axis")
	FName TurnAxis;

	UPROPERTY(EditDefaultsOnly, Category = "Input Names|Axis")
	FName TurnRateAxis;

	UPROPERTY(EditDefaultsOnly, Category = "Input Names|Axis")
	FName LookUpAxis;

	UPROPERTY(EditDefaultsOnly, Category = "Input Names|Axis")
	FName LookUpRateAxis;

};
