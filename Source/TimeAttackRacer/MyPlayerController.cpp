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
}


void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	OnlyOnce = true;
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




void AMyPlayerController::RespawnVehicle(AActor *ActorDestroyed)
{
	ATimeAttackRacerPawn* Actor = GetWorld()->SpawnActor<ATimeAttackRacerPawn>(ActorDestroyed->GetClass(), RespawnLocation);
	Possess(Actor);
	Actor->OnDestroyed.AddDynamic(this, &AMyPlayerController::RespawnVehicle);
}



void AMyPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}


void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("LeftMouse", IE_Pressed, this, &AMyPlayerController::PlayerStartGameRequest);

}

void AMyPlayerController::PlayerStartGameRequest()
{
	if (OnlyOnce)
	{
		PlayerHasStartedTheGame.Broadcast();
		OnlyOnce = false;
	}
}





