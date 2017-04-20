// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Tracker.generated.h"

UCLASS()
class TIMEATTACKRACER_API ATracker : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATracker();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Virtuals
	virtual void Tick(float DeltaTime) override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent & PropertyChangedEvent) override;



	//Atributes
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBillboardComponent* BillBoard;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomSettings")
	int32 MaxLaps;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomSettings")
	float GoldTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomSettings")
	float SilverTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomSettings")
	float BronzeTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomSettings")
	float DefaultBestLap;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomSettings")
	float DefaultBestTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomSettings")
	FText NameOfMap;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomSettings")
	FString SaveGameName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SoundEffect")
	class AAmbientSound *LevelSound; //TODO check it
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SoundEffect")
	class AAmbientSound *CheckpointSound; //TODO check it
	UPROPERTY(EditAnywhere, Category = "Checkpoint")
	TArray<class ACheckpoint*> CheckPointsList;
	UPROPERTY(EditAnywhere, Category = "Checkpoint")
	int32 TotalCheckpoint;

	class AMyPlayerController *ControllerReference;


private:
	void UpdateTimes();
	void LapCheck(int32 Checkpoint);
	void ActivateCheckpoint(class ACheckpoint *NextCheckpoint);
	bool RaceCompleteCheck();

	//Called on EndOverlap Of a checkPoint
	UFUNCTION()
	void OnCheckPointCleared(int32 CheckPointNumber);


	//Custom Event

	//Apply User Settings When Starting the Game
	void ApplySettings();
	void StartSequence();

};
