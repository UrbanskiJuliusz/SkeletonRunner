// Copyright Epic Games, Inc. All Rights Reserved.

#include "SkeletonRunnerGameMode.h"
#include "SkeletonRunnerCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASkeletonRunnerGameMode::ASkeletonRunnerGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Content/Blueprints/Player/BP_SkeletonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
