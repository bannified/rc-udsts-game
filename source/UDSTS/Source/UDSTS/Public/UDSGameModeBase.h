// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpawnPointArray.h"
#include "SpawnUnit.h"
#include "WaveLayout.h"
#include "GameFramework/GameModeBase.h"
#include "UDSGameModeBase.generated.h"

class ULevelDataAsset;

class AGameModeState;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGameModeStateChanged, AGameModeState*, OldState, AGameModeState*, NewState);

/**
 * 
 */
UCLASS()
class UDSTS_API AUDSGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Level")
	TArray< FSpawnPointArray > SpawnPointsGroups;

	UFUNCTION(BlueprintCallable, Category = "State Machine")
	void MoveToState(AGameModeState* NextState);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
	bool b_isWaveOngoing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
	int WaveNumber;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Level")
	float WaveRunningTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Level")
	ULevelDataAsset* MapLevelDataAsset;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Level")
	FWaveLayout CurrentWave;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Level")
	int CurrentSpawnUnitIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Level")
	FSpawnUnit NextSpawnUnit;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetupSpawnPointGroups();

	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void SpawnWithSpawnUnit(const FSpawnUnit spawnUnit);

	/**
	 * State Machine
	 */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "State Machine")
	AGameModeState* SavedState;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "State Machine")
	AGameModeState* CurrentState;

	UPROPERTY(BlueprintAssignable, Category = "State Machine")
	FOnGameModeStateChanged OnStateChanged;

	

};
