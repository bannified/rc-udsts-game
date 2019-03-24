// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "SpawnPoint.generated.h"

/**
 * 
 */
UCLASS()
class UDSTS_API ASpawnPoint : public ATargetPoint
{
	GENERATED_BODY()

public:
	ASpawnPoint();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Gameplay")
	TSet<int> GroupNumbers;

};
