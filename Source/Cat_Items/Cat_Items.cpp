// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved
#include "Cat_Items.h"

DEFINE_LOG_CATEGORY(LogCat_Items);

#define LOCTEXT_NAMESPACE "Cat_Items"

void FCat_Items::StartupModule()
{
	UE_LOG(LogCat_Items, Warning, TEXT("Cat_Items module has started"));
}

void FCat_Items::ShutdownModule()
{
	UE_LOG(LogCat_Items, Warning, TEXT("Cat_Items module has shut down"));
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FCat_Items, Cat_Items)