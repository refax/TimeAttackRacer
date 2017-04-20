// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Checkpoint.generated.h"

UCLASS()
class TIMEATTACKRACER_API ACheckpoint : public AActor
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCheckPointCleared, int32, NextCheckPoint);
	
public:	
	// Sets default values for this actor's properties
	ACheckpoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TextValues")
	int32	CheckPointNumber;


	FCheckPointCleared CheckPointCleared;


	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UArrowComponent *ArrowCo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent *TriggerCo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UParticleSystemComponent *ParticleSystemCo;


	void EnableCheckPoint();
	void DisableCheckpoint();

protected:
	UFUNCTION()
	void OnTriggerOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
};
