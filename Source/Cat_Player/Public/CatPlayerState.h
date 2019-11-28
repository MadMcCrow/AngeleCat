// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "CatPlayerState.generated.h"

UCLASS(ClassGroup = "Cat_Player", Category = "PlayerState")
class CAT_PLAYER_API ACatPlayerState : public APlayerState
{
	GENERATED_BODY()

public:

    virtual void BeginPlay() override;

protected:

public:

	
};
