// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved


#include "CatGameModeBase.h"
#include "Cat_GamePCH.h"


ACatGameModeBase::ACatGameModeBase(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
    DefaultPawnClass = ACatPlayerCameraPawn::StaticClass();
    PlayerControllerClass = ACatPlayerController::StaticClass();
}