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

class UUserWidget;

class AEnemyBase;

class AWaveGameModeState;

class ASetupGameModeState;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameEnd);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGameModeStateChanged, AGameModeState*, OldState, AGameModeState*, NewState);

/**
 * 
 */
UCLASS()
class UDSTS_API AUDSGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	AUDSGameModeBase();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Level")
	TArray< FSpawnPointArray > SpawnPointsGroups;

	UFUNCTION(BlueprintCallable, Category = "State Machine")
	void MoveToState(AGameModeState* NextState);

	UFUNCTION(BlueprintCallable, Category = "Gameplay Flow")
	void StartGame(ULevelDataAsset* LevelData);

	UFUNCTION(BlueprintCallable, Category = "Wave Manipulation")
	void NextWave();

	UFUNCTION(BlueprintCallable, Category = "Wave Manipulation")
	void WinGame();

	UFUNCTION(BlueprintCallable, Category = "Wave Manipulation")
	void LoseGame();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Level")
	TSubclassOf<AWaveGameModeState> WaveGameModeStateClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Level")
	TSubclassOf<ASetupGameModeState> SetupGameModeStateClass;

	UFUNCTION(BlueprintCallable, Category = "Game State")
	void OnEnemyDestroyed(AActor* EnemyDestroyed);

	UFUNCTION(BlueprintCallable, Category = "Entities")
	void HandleEnemySpawn(AActor* SpawnedEnemy);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Level")
	FSpawnUnit NextSpawnUnit;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnGameEnd OnGameWin;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnGameEnd OnGameLose;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> GameHUDWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
	bool b_isWaveOngoing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
	ULevelDataAsset* FallbackLevelData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
	int WaveNumber;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Level")
	float WaveRunningTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
	ULevelDataAsset* MapLevelDataAsset;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Level")
	FWaveLayout CurrentWave;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Level")
	int CurrentSpawnUnitIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Level")
	int CurrentWaveIndex;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetupSpawnPointGroups();

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
