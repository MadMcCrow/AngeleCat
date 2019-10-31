// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Cat_Items : ModuleRules
{
    public Cat_Items(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PrivatePCHHeaderFile = "Private/Cat_ItemsPCH.h";;

        //Public module names that this module uses.
        //In case you would like to add various classes that you're going to use in your game
        //you should add the core,coreuobject and engine dependencies.
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine" });

        //The path for the header files
        PublicIncludePaths.AddRange(new string[] { "Cat_Items/Public" });

        //The path for the source files
        PrivateIncludePaths.AddRange(new string[] { "Cat_Items/Private" });
    }
}
