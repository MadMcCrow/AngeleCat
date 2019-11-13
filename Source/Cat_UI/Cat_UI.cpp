// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#include "Cat_UI.h"

DEFINE_LOG_CATEGORY(Log_Cat_UI);

#define LOCTEXT_NAMESPACE "Log_Cat_UI"

void FCat_UI::StartupModule()
{
#if WITH_EDITOR
	UE_LOG(Log_Cat_UI, Warning, TEXT("WH_Dialogues module has started!"));
#endif //WITH_EDITOR
}

void FCat_UI::ShutdownModule()
{
#if WITH_EDITOR
	UE_LOG(Log_Cat_UI, Warning, TEXT("WH_Dialogues module has shut down"));
#endif //WITH_EDITOR
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FCat_UI, Cat_UI)