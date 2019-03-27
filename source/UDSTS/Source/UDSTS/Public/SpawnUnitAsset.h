// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SpawnUnitAsset.generated.h"

class AUnitBase;

/**
 * 
 */
UCLASS()
class UDSTS_API USpawnUnitAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Gameplay")
	TSubclassOf<AUnitBase> UnitBase;
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "UnitMod")
	void InitializeUnit(AActor* Actor);
};
