// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpawnUnit.h"
#include "EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"
#include "SpawnUnitQueryInstanceWrapper.generated.h"

/**
 * 
 */
UCLASS()
class UDSTS_API USpawnUnitQueryInstanceWrapper : public UEnvQueryInstanceBlueprintWrapper
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSpawnUnit SpawnUnit;

};
