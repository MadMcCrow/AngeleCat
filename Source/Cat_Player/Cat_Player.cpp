// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#include "Cat_Player.h"

DEFINE_LOG_CATEGORY(Log_Cat_Player);

#define LOCTEXT_NAMESPACE "Log_Cat_Player"

void FCat_Player::StartupModule()
{
#if WITH_EDITOR
	UE_LOG(Log_Cat_Player, Warning, TEXT("WH_Dialogues module has started!"));
#endif //WITH_EDITOR
}

void FCat_Player::ShutdownModule()
{
#if WITH_EDITOR
	UE_LOG(Log_Cat_Player, Warning, TEXT("WH_Dialogues module has shut down"));
#endif //WITH_EDITOR
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FCat_Player, Cat_Player)