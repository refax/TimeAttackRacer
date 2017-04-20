// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"




/**
 * 
 */
UCLASS()
class TIMEATTACKRACER_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_DELEGATE(FRaceHasStarted);
	
public:
	//Constructor
	AMyPlayerController();

	void InitText();
	void SaveGameCheck();
	void SaveTheGame();
	void LoadTheGame();
	void LapTimeCheck();
	void RaceTimeCheck();
	void UpdateGoals();


	void StartGameSetup();
	//Restart Game when the race is complete
	void Restart();
	void UpdateLap();
	UFUNCTION()
	void RespawnVehicle(AActor *ActorDestroyed);
	UFUNCTION(BlueprintCallable)
	void StartRaceTime();
	void StopRaceTime();
	UFUNCTION(BlueprintCallable)
	void StartLapTime();
	void StopLapTIme();

	void LeftMouseClick();

	// Called to bind functionality to input
	virtual void SetupInputComponent() override;
	//virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TextValues")
	FText ReadyText;

	bool RaceComplete;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TextValues")
	bool RaceStart;
	FTransform RespawnLocation;
	FString SaveSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> HUDReference;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UUserWidget* HUD;

	class ATimeAttackRacerPawn* VehicleReference;



	//Event Dispatchers
	FRaceHasStarted RaceHasStarted;


protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	bool RaceTimerEnabled;
	bool LapTimerEnabled;

	
	
};
