// Fill out your copyright notice in the Description page of Project Settings.

#include "TimeAttackRacer.h"
#include "Checkpoint.h"

#include "TimeAttackRacerPawn.h"

#include "Runtime/Engine/Classes/Components/ArrowComponent.h"
#include "Runtime/Engine/Classes/Components/SceneComponent.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"

#include "Runtime/Engine/Classes/Engine/Engine.h"

#include "Kismet/KismetMathLibrary.h"


// Sets default values
ACheckpoint::ACheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	ArrowCo = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	ArrowCo->SetupAttachment(RootComponent);

	TriggerCo = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	
	TriggerCo->SetRelativeScale3D(FVector(1.0f, 6.5f, 6.5f));
	TriggerCo->bHiddenInGame = false; 
	TriggerCo->bVisible = true; 
	TriggerCo->SetCollisionProfileName(FName("OverlapOnlyPawn"));
	TriggerCo->bGenerateOverlapEvents = true;
	TriggerCo->OnComponentEndOverlap.AddDynamic(this, &ACheckpoint::OnTriggerOverlapEnd);
	TriggerCo->SetupAttachment(RootComponent);

	ParticleSystemCo = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
	ParticleSystemCo->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ACheckpoint::EnableCheckPoint()
{
	TriggerCo->SetHiddenInGame(false);
	TriggerCo->bGenerateOverlapEvents = true;
	ParticleSystemCo->SetHiddenInGame(false);
}

void ACheckpoint::DisableCheckpoint()
{
	TriggerCo->SetHiddenInGame(true);
	TriggerCo->bGenerateOverlapEvents = false;
	ParticleSystemCo->SetHiddenInGame(true);
}


//Checkpoint cleared when overlapping occur in right direction
void ACheckpoint::OnTriggerOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ATimeAttackRacerPawn* RacerPawn = Cast<ATimeAttackRacerPawn>(OtherActor);

	if (RacerPawn)
	{
		
		FVector Velocity = RacerPawn->GetVelocity();
		

		float product = UKismetMathLibrary::Dot_VectorVector(Velocity, ArrowCo->GetComponentRotation().Vector());

		if (product > 0)
		{
			
			CheckPointCleared.Broadcast(CheckPointNumber);

			TriggerCo->SetHiddenInGame(true);
			TriggerCo->bGenerateOverlapEvents = false;
			ParticleSystemCo->SetHiddenInGame(true);

		}
	}
}



