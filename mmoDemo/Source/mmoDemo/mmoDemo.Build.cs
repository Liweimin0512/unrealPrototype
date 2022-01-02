// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class mmoDemo : ModuleRules
{
	public mmoDemo(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"HeadMountedDisplay",
		});
		
		bEnableUndefinedIdentifierWarnings = false;
		bEnableExceptions = true;
	}
}
