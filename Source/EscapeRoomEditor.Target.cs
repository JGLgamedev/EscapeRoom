// Copyright 2020-2021 Jean-Gil Langlois All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class EscapeRoomEditorTarget : TargetRules
{
	public EscapeRoomEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "EscapeRoom" } );
	}
}
