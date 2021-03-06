// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#pragma once

#include "GameFramework/PlayerController.h"
#include "CatPlayerController.generated.h"

class AGrid;
class UPlayerGridInteraction;
class UWidget;
class ACatPlayerCameraPawn;

/// @brief ACatPlayerController		Default Player controller for Cat
UCLASS(ClassGroup = "Cat_Player", Category = "PlayerController")
class CAT_PLAYER_API ACatPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	ACatPlayerController(const FObjectInitializer &ObjectInitializer = FObjectInitializer::Get());
	
	virtual void SetupInputComponent() override;
	virtual void Tick(float deltaTime) override;
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintPure, Category = "Mouse")
	bool IsUsingMouse() const;

	UFUNCTION(BlueprintCallable, Category = "Mouse")
	virtual void EnableMouse(UWidget * inWidgetToFocus);


	



};
