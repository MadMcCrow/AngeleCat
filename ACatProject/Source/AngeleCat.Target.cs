// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

using UnrealBuildTool;
using System.Collections.Generic;

public class AngeleCatTarget : TargetRules
{
	public AngeleCatTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		ExtraModuleNames.Add("AngeleCat");
        ExtraModuleNames.Add("Cat_Player");
        ExtraModuleNames.Add("Cat_UI");
		ExtraModuleNames.Add("Cat_Game");
        ExtraModuleNames.Add("Cat_Character");
		ExtraModuleNames.Add("Cat_Actors");
		ExtraModuleNames.Add("Cat_AI");
		ExtraModuleNames.Add("Cat_Interaction");
		ExtraModuleNames.Add("Cat_Animation");
		DefaultBuildSettings = BuildSettingsVersion.V2;
    }
}
