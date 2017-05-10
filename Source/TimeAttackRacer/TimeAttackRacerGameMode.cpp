// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "TimeAttackRacer.h"
#include "TimeAttackRacerGameMode.h"
#include "TimeAttackRacerPawn.h"
#include "TimeAttackRacerHud.h"
#include "MyPlayerController.h"
#include "MyGameStateBase.h"

ATimeAttackRacerGameMode::ATimeAttackRacerGameMode()
{
	DefaultPawnClass = ATimeAttackRacerPawn::StaticClass();
	HUDClass = ATimeAttackRacerHud::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();
	GameStateClass = AMyGameStateBase::StaticClass();
}
