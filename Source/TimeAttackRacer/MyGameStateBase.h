// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameStateBase.h"
#include "MyGameStateBase.generated.h"


/**
 * 
 */
UCLASS()
class TIMEATTACKRACER_API AMyGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

		DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRaceFinished);
	
	
public:
	AMyGameStateBase();

	UFUNCTION(BlueprintCallable)
	void InitText();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
		int32 ActualLap;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
		int32 MaxLaps;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
		float ActualRaceTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
		float ActualLapTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
		float GoldTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
		float SilverTIme;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
		float BronzeTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
		float BestRaceTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
		float BestLapTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
		float DefaultBestLapTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Values")
		float DefaultBestRaceTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TextValues")
		FText RaceTimeText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TextValues")
		FText CurrentLapText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TextValues")
		FText MaxLapsText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TextValues")
		FText GoldTimeText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TextValues")
		FText SilverTimeText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TextValues")
		FText BronzeTimeText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TextValues")
		FText BestTimeText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TextValues")
		FText BestLapText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TextValues")
		FText NameOfMap;

	bool RaceComplete;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TextValues")
	bool RaceStart;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TrackerManager")
	class ATracker *TrackerManager;


	UFUNCTION(BlueprintCallable)
		void StartRaceTime();
	UFUNCTION(BlueprintCallable)
		void StopRaceTime();
	UFUNCTION(BlueprintCallable)
		void StartLapTime();
	UFUNCTION(BlueprintCallable)
		void StopLapTIme();
	UFUNCTION(BlueprintCallable)
		void UpdateLap();

	UFUNCTION(BlueprintCallable)
	void LapTimeCheck();
	UFUNCTION(BlueprintCallable)
	void RaceTimeCheck();

	
	UPROPERTY(BlueprintAssignable)
	FRaceFinished OnRaceFinished;


	void RaceIsFinished();

private:
	bool RaceTimerEnabled;
	bool LapTimerEnabled;


protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
};
