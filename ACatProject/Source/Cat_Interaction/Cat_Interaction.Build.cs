// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

using UnrealBuildTool;

public class Cat_Interaction : ModuleRules

{
    public Cat_Interaction(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PrivatePCHHeaderFile = "Private/Cat_InteractionPCH.h";
        //Public module names that this module uses.
        //In case you would like to add various classes that you're going to use in your game
        //you should add the core,coreuobject and engine dependencies.
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine"});
        
        //PrivateDependencyModuleNames.AddRange(new string[] { "Cat_Player" });

        //The path for the header files
        PublicIncludePaths.AddRange(new string[] { "Cat_Interaction/Public" });

        //The path for the source files
        PrivateIncludePaths.AddRange(new string[] { "Cat_Interaction/Private" });
    }
}
 