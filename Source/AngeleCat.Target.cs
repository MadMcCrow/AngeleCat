// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class AngeleCatTarget : TargetRules
{
	public AngeleCatTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		ExtraModuleNames.Add("AngeleCat");
        ExtraModuleNames.Add("Cat_Player");
        ExtraModuleNames.Add("Cat_Character");
        ExtraModuleNames.Add("Cat_Items");
    }
}
