// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#pragma once

#include "CatGameModeBase.h"
#include "CatGameModeExploration.generated.h"

/**
 * 
 */
UCLASS(Category = "GameMode", ClassGroup="Cat_Game")
class CAT_GAME_API ACatGameModeExploration : public ACatGameModeBase
{
	GENERATED_BODY()

public:
	ACatGameModeExploration(const FObjectInitializer &ObjectInitializer);
	
};
