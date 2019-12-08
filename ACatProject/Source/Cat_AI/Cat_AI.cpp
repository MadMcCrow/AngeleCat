// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#include "Cat_AI.h"

DEFINE_LOG_CATEGORY(Log_Cat_AI);

#define LOCTEXT_NAMESPACE "Log_Cat_AI"

void FCat_AI::StartupModule()
{
#if WITH_EDITOR
	UE_LOG(Log_Cat_AI, Warning, TEXT("WH_Dialogues module has started!"));
#endif //WITH_EDITOR
}

void FCat_AI::ShutdownModule()
{
#if WITH_EDITOR
	UE_LOG(Log_Cat_AI, Warning, TEXT("WH_Dialogues module has shut down"));
#endif //WITH_EDITOR
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FCat_AI, Cat_AI)