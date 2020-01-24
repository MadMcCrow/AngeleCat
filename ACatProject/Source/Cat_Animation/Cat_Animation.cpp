// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved
#include "Cat_Animation.h"

DEFINE_LOG_CATEGORY(LogCat_Animation);

#define LOCTEXT_NAMESPACE "Cat_Animation"

void FCat_Animation::StartupModule()
{
	UE_LOG(LogCat_Animation, Warning, TEXT("Cat_Animation module has started"));
}

void FCat_Animation::ShutdownModule()
{
	UE_LOG(LogCat_Animation, Warning, TEXT("Cat_Animation module has shut down"));
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FCat_Animation, Cat_Animation)