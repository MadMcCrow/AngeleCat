// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#include "Cat_Game.h"

DEFINE_LOG_CATEGORY(Log_Cat_Game);

#define LOCTEXT_NAMESPACE "Log_Cat_Game"

void FCat_Game::StartupModule()
{
#if WITH_EDITOR
	UE_LOG(Log_Cat_Game, Warning, TEXT("WH_Dialogues module has started!"));
#endif //WITH_EDITOR
}

void FCat_Game::ShutdownModule()
{
#if WITH_EDITOR
	UE_LOG(Log_Cat_Game, Warning, TEXT("WH_Dialogues module has shut down"));
#endif //WITH_EDITOR
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FCat_Game, Cat_Game)