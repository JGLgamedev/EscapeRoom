// Copyright 2020-2021 Jean-Gil Langlois All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class EscapeRoomTarget : TargetRules
{
	public EscapeRoomTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "EscapeRoom" } );
	}
}
