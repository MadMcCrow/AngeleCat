// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

using UnrealBuildTool;

public class AngeleCat : ModuleRules
{
	public AngeleCat(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule" });
        PrivateDependencyModuleNames.AddRange(new string[] { "Cat_Player", "Cat_Character" });
        PrivateDependencyModuleNames.AddRange(new string[] { "Cat_Animation" });
    }
}
