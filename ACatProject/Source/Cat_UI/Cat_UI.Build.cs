// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

using UnrealBuildTool;

public class Cat_UI : ModuleRules

{
    public Cat_UI(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PrivatePCHHeaderFile = "Private/Cat_UIPCH.h";
        //Public module names that this module uses.
        //In case you would like to add various classes that you're going to use in your game
        //you should add the core,coreuobject and engine dependencies.
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine"});
        PublicDependencyModuleNames.AddRange(new string[] { "UMG"});
        
        //PrivateDependencyModuleNames.AddRange(new string[] { "Cat_Player" });

        //The path for the header files
        PublicIncludePaths.AddRange(new string[] { "Cat_UI/Public" });

        //The path for the source files
        PrivateIncludePaths.AddRange(new string[] { "Cat_UI/Private" });
    }
}
 