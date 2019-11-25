// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CatHUD.generated.h"

// forward declaration
class UUserWidget;

/**
 * 
 */
UCLASS(Config=Game)
class CAT_PLAYER_API ACatHUD : public AHUD
{
	GENERATED_BODY()

public:

	UPROPERTY(Config, BlueprintReadOnly, Category = "Widget")
	TSubclassOf<UUserWidget> MainwidgetClass;

	UFUNCTION(BlueprintCallable, Category = "Widget")
	void SpawnHUDWidget();

private:

	UPROPERTY()
	UUserWidget* MainHUDWidget;
};
