// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class AngeleCatEditorTarget : TargetRules
{
	public AngeleCatEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
        ExtraModuleNames.Add("AngeleCat");
        ExtraModuleNames.Add("Cat_Player");
        ExtraModuleNames.Add("Cat_Character");
        ExtraModuleNames.Add("Cat_Items");
    }
}
