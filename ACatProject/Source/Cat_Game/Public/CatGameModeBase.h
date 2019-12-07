// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CatGameModeBase.generated.h"

/**
 * 	Base class for all game modes
 */
UCLASS(Category = "GameMode", ClassGroup="Cat_Game")
class CAT_GAME_API ACatGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACatGameModeBase(const FObjectInitializer &ObjectInitializer);

};
