// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BombBot : ModuleRules
{
	public BombBot(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "Niagara", "AIModule", "NavigationSystem", "UMG", "Slate", "SlateCore"  });
	}
}
