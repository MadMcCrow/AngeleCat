// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#pragma once

#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(LogCat_Animation_Editor, All, All);

class FCat_Animation_Editor : public IModuleInterface
{
public:

	/* This will get called when the editor loads the module */
	virtual void StartupModule() override;

	/* This will get called when the editor unloads the module */
	virtual void ShutdownModule() override;
};