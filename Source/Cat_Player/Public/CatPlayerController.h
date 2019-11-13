// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#pragma once

#include "GameFramework/PlayerController.h"
#include "CatPlayerController.generated.h"

class AGrid;
class UPlayerGridInteraction;

/// @brief ACatPlayerController		Default Player controller for Cat
UCLASS(ClassGroup=(PlayerController))
class CAT_PLAYER_API ACatPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	ACatPlayerController(const FObjectInitializer &ObjectInitializer = FObjectInitializer::Get());
	
	virtual void SetupInputComponent() override;
	virtual void Tick(float deltaTime) override;

	UFUNCTION(BlueprintPure, Category = "Mouse")
	bool IsUsingMouse() const;



protected :

	UFUNCTION()
	virtual void OnClick();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid")
	UPlayerGridInteraction * GridInteractComp;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    FName ClickActionName;

	UFUNCTION()
	void UpdateGridInteractionCursorPosition();
	



};
