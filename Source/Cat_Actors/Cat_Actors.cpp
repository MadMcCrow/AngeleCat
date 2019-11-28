// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#include "Cat_Actors.h"

DEFINE_LOG_CATEGORY(Log_Cat_Actors);

#define LOCTEXT_NAMESPACE "Log_Cat_Actors"

void FCat_Actors::StartupModule()
{
#if WITH_EDITOR
	UE_LOG(Log_Cat_Actors, Warning, TEXT("Cat Actors module has started!"));
#endif //WITH_EDITOR
}

void FCat_Actors::ShutdownModule()
{
#if WITH_EDITOR
	UE_LOG(Log_Cat_Actors, Warning, TEXT("Cat Actors module has shut down"));
#endif //WITH_EDITOR
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FCat_Actors, Cat_Actors)