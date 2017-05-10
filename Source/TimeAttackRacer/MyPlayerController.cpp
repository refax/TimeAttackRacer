// Fill out your copyright notice in the Description page of Project Settings.

#include "TimeAttackRacer.h"
#include "MyPlayerController.h"

#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "TimeAttackRacerPawn.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Runtime/Engine/Classes/Components/TimelineComponent.h"
#include "UtilityFunction.h"


AMyPlayerController::AMyPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	HUD = nullptr;
	VehicleReference = nullptr;


	ActualLap = 1;
	MaxLaps = 3;

	RaceTimerEnabled = false;
	LapTimerEnabled = false;
	ActualLapTime = 0.0f;
	ActualRaceTime = 0.0f;

}

void AMyPlayerController::InitText()
{
	CurrentLapText = FText::FromString(FString::FromInt(ActualLap));
	MaxLapsText = FText::FromString(FString::FromInt(MaxLaps));

	GoldTimeText = FText::FromString(UtilityFunction::TimeToText(GoldTime));
	SilverTimeText = FText::FromString(UtilityFunction::TimeToText(SilverTIme));
	BronzeTimeText = FText::FromString(UtilityFunction::TimeToText(BronzeTime));
	
	BestLapText = FText::FromString(UtilityFunction::TimeToText(BestLapTime));
	BestTimeText = FText::FromString(UtilityFunction::TimeToText(BestRaceTime));
}

void AMyPlayerController::SaveGameCheck()
{
	BestRaceTime = DefaultBestRaceTime;
	BestLapTime = DefaultBestLapTime;
}

void AMyPlayerController::SaveTheGame()
{

}

void AMyPlayerController::LoadTheGame()
{

}

//Lap time check-Check if we have a new lap record
void AMyPlayerController::LapTimeCheck()
{
	StopLapTIme();

	if (ActualLapTime < BestLapTime)
	{
		BestLapTime = ActualLapTime;
		BestLapText = FText::FromString(UtilityFunction::TimeToText(BestLapTime));
		SaveTheGame();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT(""+UtilityFunction::TimeToText(BestLapTime)));
	}
	
	ActualLapTime = 0.0f;

	if (RaceComplete)
	{
		RaceTimeCheck();
	}
	{
		StartLapTime();
	}
}

//RaceTimeCheck- Save the best race time if we have a new record
void AMyPlayerController::RaceTimeCheck()
{
	if (ActualRaceTime <= BestRaceTime)
	{
		BestRaceTime = ActualRaceTime;
		BestTimeText = FText::FromString(UtilityFunction::TimeToText(BestRaceTime));
		SaveTheGame();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("" + UtilityFunction::TimeToText(BestRaceTime)));
	}
}

void AMyPlayerController::UpdateGoals()
{

}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	
	//UUserWidget *HUD = //Cast<UUserWidget>(HUDReference->class);
	//UUserWidget *HUD = HUDReference->GetDefaultObject<UUserWidget>();
	UUserWidget *HUD = CreateWidget<UUserWidget>(this, HUDReference);
	if(HUD)
		HUD->AddToViewport();

	VehicleReference = Cast<ATimeAttackRacerPawn>(GetControlledPawn());

	if (VehicleReference)
	{
		VehicleReference->OnDestroyed.AddDynamic(this, &AMyPlayerController::RespawnVehicle);
	}

	//StartRaceTime();
	//StartLapTime();
	
	
}


//Private

//Start Game Sequence
void AMyPlayerController::StartGameSetup()
{
	SaveGameCheck();
	InitText();
	
}

//Restart Game when the race is complete
void AMyPlayerController::Restart() 
{
	RaceStart = false;

	//Delay???

	RestartLevel();

}

void AMyPlayerController::UpdateLap()
{
	if (!RaceComplete)
	{
		ActualLap++;
		CurrentLapText = FText::FromString(FString::FromInt(ActualLap));
	}
	LapTimeCheck();
	UKismetSystemLibrary::PrintText(this, CurrentLapText);
}

void AMyPlayerController::RespawnVehicle(AActor *ActorDestroyed)
{
	ATimeAttackRacerPawn* Actor = GetWorld()->SpawnActor<ATimeAttackRacerPawn>(ActorDestroyed->GetClass(), RespawnLocation);
	Possess(Actor);
	Actor->OnDestroyed.AddDynamic(this, &AMyPlayerController::RespawnVehicle);
}

void AMyPlayerController::StartRaceTime()
{
	RaceTimerEnabled = true;
	//ActualRaceTime = 0.0f;
}

void AMyPlayerController::StopRaceTime()
{
	RaceTimerEnabled = false;
}

void AMyPlayerController::StartLapTime()
{
	LapTimerEnabled = true;

}

void AMyPlayerController::StopLapTIme()
{
	LapTimerEnabled = false;
}

void AMyPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//Update race timer
	if (RaceTimerEnabled)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT(""+UtilityFunction::TimeToText(ActualRaceTime)));
		ActualRaceTime += DeltaTime;
		RaceTimeText = FText::FromString(UtilityFunction::TimeToText(ActualRaceTime));
		UpdateGoals();
	}

	//Update lap timer
	if (LapTimerEnabled)
	{
		ActualLapTime += DeltaTime;
	}

}


void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}

void AMyPlayerController::LeftMouseClick()
{
	//Do Once
	//if (!RaceStart)
	//{

	//}
}


