// Copyright Epic Games, Inc. All Rights Reserved.

#include "SocketTestGameMode.h"
#include "SocketTestCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASocketTestGameMode::ASocketTestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
