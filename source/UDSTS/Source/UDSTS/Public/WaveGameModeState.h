// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameModeState.h"
#include "WaveLayout.h"
#include "SpawnUnit.h"
#include "EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "WaveGameModeState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWaveCleared);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWaveFinishSpawning);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyUnitSpawned, AActor*, EnemyUnit);

/**
 * 
 */
UCLASS()
class UDSTS_API AWaveGameModeState : public AGameModeState
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	float RunningTime;

	UFUNCTION(BlueprintCallable, Category = "WaveState")
	void Init(FWaveLayout WaveLayout);

	void SpawnQueryFinished(TSharedPtr<FEnvQueryResult> Result);

	UFUNCTION(BlueprintCallable, Category = "WaveState")
	void SpawnWithSpawnUnit(FSpawnUnit SpawnUnit);

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Events")
	FWaveCleared WaveClearedEvent;

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Events")
	FOnEnemyUnitSpawned OnEnemyUnitSpawned;

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Events")
	FWaveFinishSpawning WaveFinishSpawning;

	virtual void OnStateEnter(AUDSGameModeBase* GameMode) override;

	virtual void OnStateStart(AUDSGameModeBase* GameMode) override;

	virtual void OnStateTick(AUDSGameModeBase* GameMode, const float DeltaTime) override;

	virtual void OnStateStop(AUDSGameModeBase* GameMode) override;

	/**
	 * Wave Spawning Members
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Wave")
	FWaveLayout CurrentWaveLayout;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Wave")
	TArray< FSpawnUnit > SpawnUnits;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Wave")
	FSpawnUnit NextSpawnUnit;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Wave")
	int32 CurrentSpawnUnitIndex;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EQS")
	UEnvQuery* SpawnQuery;
};
