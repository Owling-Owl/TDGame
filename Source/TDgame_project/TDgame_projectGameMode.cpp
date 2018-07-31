// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "TDgame_projectGameMode.h"
#include "TDgame_projectCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATDgame_projectGameMode::ATDgame_projectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
