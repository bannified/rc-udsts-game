// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "WaveDefenseGameState.generated.h"

class ABase;
class USpawnUnitAsset;

/**
 * 
 */
UCLASS()
class UDSTS_API AWaveDefenseGameState : public AGameStateBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scorekeeping")
	int32 TotalScore;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scorekeeping")
	int32 EnemiesLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scorekeeping")
	int32 EnemiesLeaked;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game World")
	ABase* BaseOfInterest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game World")
	TArray< ABase* > BasesInLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scorekeeping")
	TMap< USpawnUnitAsset*, int32 > SpawnUnitToKillCountMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scorekeeping")
	TMap< USpawnUnitAsset*, int32 > SpawnUnitToLeakCountMap;
};
