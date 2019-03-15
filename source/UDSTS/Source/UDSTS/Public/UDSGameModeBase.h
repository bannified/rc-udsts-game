// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpawnPointArray.h"
#include "SpawnUnit.h"
#include "WaveLayout.h"
#include "GameFramework/GameModeBase.h"
#include "UDSGameModeBase.generated.h"

class ULevelDataAsset;

/**
 * 
 */
UCLASS()
class UDSTS_API AUDSGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Level")
	TArray< FSpawnPointArray > SpawnPointsGroups;

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

};
