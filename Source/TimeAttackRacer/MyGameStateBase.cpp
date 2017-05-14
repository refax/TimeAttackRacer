// Fill out your copyright notice in the Description page of Project Settings.

#include "TimeAttackRacer.h"
#include "MyGameStateBase.h"

#include "UtilityFunction.h"

#include "Tracker.h"

#include "Runtime/Engine/Classes/Engine/Engine.h"


AMyGameStateBase::AMyGameStateBase()
{

	PrimaryActorTick.bCanEverTick = true;

	TrackerManager = nullptr;

	ActualLap = 1;
	MaxLaps = 3;

	RaceTimerEnabled = false;
	LapTimerEnabled = false;
	ActualLapTime = 0.0f;
	ActualRaceTime = 0.0f;
}


void AMyGameStateBase::BeginPlay()
{
	Super::BeginPlay();
}

//Initialisaztion is made by the GameStateManager that connects Tracker and GameState
void AMyGameStateBase::InitText()
{
	if (TrackerManager)
	{
		GoldTime = TrackerManager->GoldTime;
		SilverTIme = TrackerManager->SilverTime;
		BronzeTime = TrackerManager->BronzeTime;
		DefaultBestLapTime = TrackerManager->DefaultBestLap;
		DefaultBestRaceTime = TrackerManager->DefaultBestTime;
		MaxLaps = TrackerManager->MaxLaps;

		TrackerManager->OnLapIsFinished.AddDynamic(this, &AMyGameStateBase::UpdateLap);
		TrackerManager->OnRaceIsFinished.AddDynamic(this, &AMyGameStateBase::RaceIsFinished);

	}

	CurrentLapText = FText::FromString(FString::FromInt(ActualLap));
	MaxLapsText = FText::FromString(FString::FromInt(MaxLaps));

	GoldTimeText = FText::FromString(UtilityFunction::TimeToText(GoldTime));
	SilverTimeText = FText::FromString(UtilityFunction::TimeToText(SilverTIme));
	BronzeTimeText = FText::FromString(UtilityFunction::TimeToText(BronzeTime));

	BestLapText = FText::FromString(UtilityFunction::TimeToText(BestLapTime));
	BestTimeText = FText::FromString(UtilityFunction::TimeToText(BestRaceTime));
}

void AMyGameStateBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Update race timer
	if (RaceTimerEnabled)
	{
		ActualRaceTime += DeltaTime;
		RaceTimeText = FText::FromString(UtilityFunction::TimeToText(ActualRaceTime));
	}

	//Update lap timer
	if (LapTimerEnabled)
	{
		ActualLapTime += DeltaTime;
	}

}

void AMyGameStateBase::StartRaceTime()
{
	RaceTimerEnabled = true;
	ActualRaceTime = 0.0f;
}

void AMyGameStateBase::StopRaceTime()
{
	RaceTimerEnabled = false;
}

void AMyGameStateBase::StartLapTime()
{
	LapTimerEnabled = true;

}

void AMyGameStateBase::StopLapTIme()
{
	LapTimerEnabled = false;
}

void AMyGameStateBase::UpdateLap()
{
	
	if (TrackerManager)
	{
		ActualLap++;
	}

	CurrentLapText = FText::FromString(FString::FromInt(ActualLap));
	//}
	LapTimeCheck();
	//UKismetSystemLibrary::PrintText(this, CurrentLapText);
	
}

//Lap time check-Check if we have a new lap record
void AMyGameStateBase::LapTimeCheck()
{
	
	StopLapTIme();

	if (ActualLapTime < BestLapTime)
	{
	BestLapTime = ActualLapTime;
	BestLapText = FText::FromString(UtilityFunction::TimeToText(BestLapTime));
	
	}

	ActualLapTime = 0.0f;
	/*
	if (RaceComplete)
	{
	RaceTimeCheck();
	}
	{
	
	}*/

	StartLapTime();
	
}

//RaceTimeCheck- Save the best race time if we have a new record
void AMyGameStateBase::RaceTimeCheck()
{
	
	if (ActualRaceTime <= BestRaceTime)
	{
	BestRaceTime = ActualRaceTime;
	BestTimeText = FText::FromString(UtilityFunction::TimeToText(BestRaceTime));
	
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("" + UtilityFunction::TimeToText(BestRaceTime)));
	}
}


void AMyGameStateBase::RaceIsFinished()
{
	RaceTimeCheck();

	OnRaceFinished.Broadcast();
}