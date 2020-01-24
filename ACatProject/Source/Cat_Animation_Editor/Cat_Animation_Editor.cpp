// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved
#include "Cat_Animation_Editor.h"

DEFINE_LOG_CATEGORY(LogCat_Animation_Editor);

#define LOCTEXT_NAMESPACE "Cat_Animation_Editor"

void FCat_Animation_Editor::StartupModule()
{
	UE_LOG(LogCat_Animation_Editor, Warning, TEXT("Cat_Animation_Editor module has started"));
}

void FCat_Animation_Editor::ShutdownModule()
{
	UE_LOG(LogCat_Animation_Editor, Warning, TEXT("Cat_Animation_Editor module has shut down"));
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FCat_Animation_Editor, Cat_Animation_Editor)