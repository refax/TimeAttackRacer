// Fill out your copyright notice in the Description page of Project Settings.

#include "TimeAttackRacer.h"
#include "MyGameStateBase.h"

#include "UtilityFunction.h"


AMyGameStateBase::AMyGameStateBase()
{

	PrimaryActorTick.bCanEverTick = true;

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


void AMyGameStateBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Update race timer
	if (RaceTimerEnabled)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT(""+UtilityFunction::TimeToText(ActualRaceTime)));
		ActualRaceTime += DeltaTime;
		RaceTimeText = FText::FromString(UtilityFunction::TimeToText(ActualRaceTime));
		//UpdateGoals();
	}

	//Update lap timer
	if (LapTimerEnabled)
	{
		ActualLapTime += DeltaTime;
	}

}