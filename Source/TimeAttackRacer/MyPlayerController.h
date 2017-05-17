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

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerHasStartedTheGame);


public:
	//Constructor
	AMyPlayerController();
	
	UFUNCTION()
	void RespawnVehicle(AActor *ActorDestroyed);


	void PlayerStartGameRequest();


	// Called to bind functionality to input
	virtual void SetupInputComponent() override;
	//virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTransform RespawnLocation;
	FString SaveSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> HUDReference;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UUserWidget* HUD;

	class ATimeAttackRacerPawn* VehicleReference;



	//Event Dispatchers
	FRaceHasStarted RaceHasStarted;

	UPROPERTY(BlueprintAssignable)
	FPlayerHasStartedTheGame PlayerHasStartedTheGame;


protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	bool OnlyOnce;


};
