// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

using UnrealBuildTool;

public class Cat_Animation_Editor : ModuleRules
{
    public Cat_Animation_Editor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PrivatePCHHeaderFile = "Private/Cat_Animation_EditorPCH.h";

        // UE4 Modules
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine" /*,"AnimGraph"*/});
        PublicDependencyModuleNames.AddRange(new string[] { "AnimGraph", "BlueprintGraph" });
        
        // Cat Modules 
        PublicDependencyModuleNames.AddRange(new string[] { "Cat_Animation" });

        //The path for the header files
        PublicIncludePaths.AddRange(new string[] { "Cat_Animation_Editor/Public" });
        //The path for the source files
        PrivateIncludePaths.AddRange(new string[] { "Cat_Animation_Editor/Private" });
    }
}
