// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/HUD.h"
#include "TimeAttackRacerHud.generated.h"


UCLASS(config = Game)
class ATimeAttackRacerHud : public AHUD
{
	GENERATED_BODY()

public:
	ATimeAttackRacerHud();

	/** Font used to render the vehicle info */
	UPROPERTY()
	UFont* HUDFont;

	// Begin AHUD interface
	virtual void DrawHUD() override;
	// End AHUD interface

	UPROPERTY()
	class AMyPlayerController* PlayerController;

protected:
	virtual void BeginPlay() override;

};
