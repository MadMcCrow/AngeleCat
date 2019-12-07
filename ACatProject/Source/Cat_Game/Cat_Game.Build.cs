// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

using UnrealBuildTool;

public class Cat_Game : ModuleRules

{
    public Cat_Game(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PrivatePCHHeaderFile = "Private/Cat_GamePCH.h";
        //Public module names that this module uses.
        //In case you would like to add various classes that you're going to use in your game
        //you should add the core,coreuobject and engine dependencies.
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine"});
        PrivateDependencyModuleNames.AddRange(new string[] { "Cat_Player" });
        PrivateDependencyModuleNames.AddRange(new string[] { "Cat_Character" });

        //The path for the header files
        PublicIncludePaths.AddRange(new string[] { "Cat_Game/Public" });

        //The path for the source files
        PrivateIncludePaths.AddRange(new string[] { "Cat_Game/Private" });
    }
}
 