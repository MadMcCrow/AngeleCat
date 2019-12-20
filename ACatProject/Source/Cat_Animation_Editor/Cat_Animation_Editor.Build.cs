// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Cat_Animation_Editor : ModuleRules
{
    public Cat_Animation_Editor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PrivatePCHHeaderFile = "Private/Cat_Animation_EditorPCH.h";

        //Public module names that this module uses.
        //In case you would like to add various classes that you're going to use in your game
        //you should add the core,coreuobject and engine dependencies.
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine" });
        
        //The path for the header files
        PublicIncludePaths.AddRange(new string[] { "Cat_Animation_Editor/Public" });

        //The path for the source files
        PrivateIncludePaths.AddRange(new string[] { "Cat_Animation_Editor/Private" });
    }
}
