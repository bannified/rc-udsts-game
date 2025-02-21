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

class APlayerControllerBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameEnd);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGameModeStateChanged, AGameModeState*, OldState, AGameModeState*, NewState);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FEnemyKilled, AActor*, Victim, AActor*, Killer);

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

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Events")
	FOnGameEnd OnGameWin;

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Events")
	FOnGameEnd OnGameLose;

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Events")
	FOnGameEnd OnNextWave;

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Events")
	FOnGameEnd OnWaveCleared;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Level")
	bool b_GameWon = false;

	UFUNCTION(BlueprintCallable, Category = "Events")
	void OnEnemyDeath(AActor* Victim, AActor* Killer);

	UFUNCTION(BlueprintCallable, Category = "Events")
	void OnBaseTakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly, Category = "Player Management")
	TArray<APlayerController*> PlayerControllerList;

	UFUNCTION(BlueprintCallable, Category = "Player Management")
	virtual void RegisterPlayer(APlayerController* playerController);

	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

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
