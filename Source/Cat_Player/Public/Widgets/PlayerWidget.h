// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerWidget.generated.h"

class UCatValueWidget;
class ACatPlayerState;

/**
 * 
 */
UCLASS()
class CAT_PLAYER_API UPlayerWidget : public UUserWidget
{
	GENERATED_BODY()
	
	friend ACatPlayerState;

    virtual void OnWidgetRebuilt() override;

private:


	

};


