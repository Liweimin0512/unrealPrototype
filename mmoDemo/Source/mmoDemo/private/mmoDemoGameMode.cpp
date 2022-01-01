// Copyright Epic Games, Inc. All Rights Reserved.

#include "mmoDemo/Public/mmoDemoGameMode.h"
#include "mmoDemo/Public/mmoDemoCharacter.h"
#include "UObject/ConstructorHelpers.h"

AmmoDemoGameMode::AmmoDemoGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
