// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpawnPointArray.h"
#include "GameFramework/GameModeBase.h"
#include "UDSGameModeBase.generated.h"

//struct FWaveLayout;

/**
 * 
 */
UCLASS()
class UDSTS_API AUDSGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Spawning")
	TArray< FSpawnPointArray > SpawnPointsGroups;

private:
	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetupSpawnPointGroups();

};
