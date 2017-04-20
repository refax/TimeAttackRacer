// Fill out your copyright notice in the Description page of Project Settings.

#include "TimeAttackRacer.h"
#include "Tracker.h"
#include "Runtime/Engine/Classes/Components/BillboardComponent.h"
#include "Runtime/Engine/Classes/Sound/AmbientSound.h"
#include "MyPlayerController.h"
#include "Checkpoint.h"

#include "Runtime/Engine/Classes/Engine/Engine.h"


// Sets default values
ATracker::ATracker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BillBoard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));

	MaxLaps = 2;
	GoldTime = 60.0f;
	SilverTime = 120.0f;
	BronzeTime = 180.0f;

	DefaultBestLap = 60.0f;
	DefaultBestTime = 120.0f;
	NameOfMap = FText::FromString("Time Attack Map");
	SaveGameName = "LL_SaveGame";

	LevelSound = nullptr;
	CheckpointSound = nullptr;

	TotalCheckpoint = 0;

	ControllerReference = nullptr;
}

// Called when the game starts or when spawned
void ATracker::BeginPlay()
{
	Super::BeginPlay();

	//Set player controller
	UWorld *World = GetWorld();
	if (World)
	{
		ControllerReference = Cast<AMyPlayerController>(World->GetFirstPlayerController());
	}

	ApplySettings();

	StartSequence();

}

// Called every frame
void ATracker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATracker::PostEditChangeProperty(FPropertyChangedEvent & PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	CheckPointsList.SetNum(TotalCheckpoint);
}

//private functions
void ATracker::UpdateTimes()
{
	if (ControllerReference)
	{
		ControllerReference->GoldTime = GoldTime;
		ControllerReference->SilverTIme = SilverTime;
		ControllerReference->BronzeTime = BronzeTime;
		ControllerReference->DefaultBestLapTime = DefaultBestLap;
		ControllerReference->DefaultBestRaceTime = DefaultBestTime;
	}
}

//Check if Lap is finished, if no update
void ATracker::LapCheck(int32 Checkpoint)
{
	if (ControllerReference)
	{
		if (TotalCheckpoint == Checkpoint)
		{
			if (!RaceCompleteCheck())
			{
				
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("LapCompleted"));
				ActivateCheckpoint(CheckPointsList[0]);
				ControllerReference->UpdateLap();
				ControllerReference->RespawnLocation = CheckPointsList[Checkpoint - 1]->GetActorTransform();
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("RaceCompleted"));
				ControllerReference->UpdateLap();
			}

		}
		else
		{
			ActivateCheckpoint(CheckPointsList[Checkpoint]);
			ControllerReference->RespawnLocation = CheckPointsList[Checkpoint - 1]->GetActorTransform();		
		}
	}
}

//This will Activate next Checkpoint
void ATracker::ActivateCheckpoint( ACheckpoint *NextCheckpoint)
{
	NextCheckpoint->EnableCheckPoint();
	
}

bool ATracker::RaceCompleteCheck()
{

	bool IsRaceComplete = false;
	if (ControllerReference)
	{
		ControllerReference->RaceComplete = (ControllerReference->ActualLap >= ControllerReference->MaxLaps);
		IsRaceComplete = ControllerReference->RaceComplete;
	}

	return IsRaceComplete;
}

//Custom Events
void ATracker::ApplySettings()
{
	if (ControllerReference)
	{
		ControllerReference->MaxLaps = MaxLaps;

		UpdateTimes();

		ControllerReference->StartGameSetup();
	}
}

//Start Sequence / Init all checkpoints and Activate the First Checkpoint and Bind Event TO checkPoint
void ATracker::StartSequence()
{
	for (int32 i = 0; i < TotalCheckpoint; ++i)
	{
		ACheckpoint* CurrentCheckpoint = CheckPointsList[i];
		if (CurrentCheckpoint)
		{
			CurrentCheckpoint->CheckPointNumber = i + 1;
			CurrentCheckpoint->CheckPointCleared.AddDynamic(this, &ATracker::OnCheckPointCleared);
			if (i == 0) //If is the First CheckPoint Activate it
			{
				ActivateCheckpoint(CurrentCheckpoint);
			}
			else
			{
				CurrentCheckpoint->DisableCheckpoint();
			}

		}
	}

	//Start Music
	if (LevelSound)
	{
		LevelSound->Play();
	}
}

//Check and see if race is over and if so, restarted
void ATracker::OnCheckPointCleared(int32 CheckPointNumber)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("ActorEndOverlap!2"));
	LapCheck(CheckPointNumber);

	if (CheckpointSound)
	{
		CheckpointSound->Play();
	}

	if (ControllerReference)
	{
		if (ControllerReference->RaceComplete)
		{
			ControllerReference->Restart();
		}
	}

}