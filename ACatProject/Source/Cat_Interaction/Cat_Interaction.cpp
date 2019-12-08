// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#include "Cat_Interaction.h"

DEFINE_LOG_CATEGORY(Log_Cat_Interaction);

#define LOCTEXT_NAMESPACE "Log_Cat_Interaction"

void FCat_Interaction::StartupModule()
{
#if WITH_EDITOR
	UE_LOG(Log_Cat_Interaction, Warning, TEXT("Cat UI module has started!"));
#endif //WITH_EDITOR
}

void FCat_Interaction::ShutdownModule()
{
#if WITH_EDITOR
	UE_LOG(Log_Cat_Interaction, Warning, TEXT("Cat UI module has shut down"));
#endif //WITH_EDITOR
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FCat_Interaction, Cat_Interaction)