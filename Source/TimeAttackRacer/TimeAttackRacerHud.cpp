// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "TimeAttackRacer.h"
#include "TimeAttackRacerHud.h"
#include "TimeAttackRacerPawn.h"
#include "Engine/Canvas.h"
#include "Engine/Font.h"
#include "CanvasItem.h"
#include "MyPlayerController.h"

// Needed for VR Headset
#include "Engine.h"
#if HMD_MODULE_INCLUDED
#include "IHeadMountedDisplay.h"
#endif  // HMD_MODULE_INCLUDED
#define LOCTEXT_NAMESPACE "VehicleHUD"

ATimeAttackRacerHud::ATimeAttackRacerHud()
{
	static ConstructorHelpers::FObjectFinder<UFont> Font(TEXT("/Engine/EngineFonts/RobotoDistanceField"));
	HUDFont = Font.Object;
	PlayerController = nullptr;
}

void ATimeAttackRacerHud::DrawHUD()
{
	Super::DrawHUD();

	if (PlayerController)
	{
		if (PlayerController->RaceStart)
		{
			


	// Calculate ratio from 720p
	const float HUDXRatio = Canvas->SizeX / 1280.f;
	const float HUDYRatio = Canvas->SizeY / 720.f;

	bool bHMDDeviceActive = false;

	// We dont want the onscreen hud when using a HMD device	
#if HMD_MODULE_INCLUDED
	if (GEngine->HMDDevice.IsValid() == true )
	{
		bHMDDeviceActive = GEngine->HMDDevice->IsStereoEnabled();
	}
#endif // HMD_MODULE_INCLUDED
	if( bHMDDeviceActive == false )
	{
		// Get our vehicle so we can check if we are in car. If we are we don't want onscreen HUD
		ATimeAttackRacerPawn* Vehicle = Cast<ATimeAttackRacerPawn>(GetOwningPawn());
		if ((Vehicle != nullptr) && (Vehicle->bInCarCameraActive == false))
		{
			FVector2D ScaleVec(HUDYRatio * 1.4f, HUDYRatio * 1.4f);

			// Speed
			FCanvasTextItem SpeedTextItem(FVector2D(HUDXRatio * 805.f, HUDYRatio * 455), Vehicle->SpeedDisplayString, HUDFont, FLinearColor::White);
			SpeedTextItem.Scale = ScaleVec;
			Canvas->DrawItem(SpeedTextItem);

			// Gear
			FCanvasTextItem GearTextItem(FVector2D(HUDXRatio * 805.f, HUDYRatio * 500.f), Vehicle->GearDisplayString, HUDFont, Vehicle->bInReverseGear == false ? Vehicle->GearDisplayColor : Vehicle->GearDisplayReverseColor);
			GearTextItem.Scale = ScaleVec;
			Canvas->DrawItem(GearTextItem);
		}
	}
		}
	}
}

void ATimeAttackRacerHud::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	PlayerController = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("BeginPlayHUD!"));
}

#undef LOCTEXT_NAMESPACE
