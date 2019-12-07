// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved


#include "CatGameModeExploration.h"
#include "Cat_GamePCH.h"
#include "CatPlayerPawn.h"


ACatGameModeExploration::ACatGameModeExploration(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
    DefaultPawnClass = ACatPlayerPawn::StaticClass();
}