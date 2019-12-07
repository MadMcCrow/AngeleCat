// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved
#include "Cat_Character.h"

DEFINE_LOG_CATEGORY(LogCat_Character);

#define LOCTEXT_NAMESPACE "Cat_Character"

void FCat_Character::StartupModule()
{
	UE_LOG(LogCat_Character, Warning, TEXT("Cat_Character module has started"));
}

void FCat_Character::ShutdownModule()
{
	UE_LOG(LogCat_Character, Warning, TEXT("Cat_Character module has shut down"));
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FCat_Character, Cat_Character)