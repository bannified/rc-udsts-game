// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "EnemyTest.generated.h"

/**
 * 
 */
UCLASS()
class UDSTS_API AEnemyTest : public AEnemyBase
{
	GENERATED_BODY()

public:
	AEnemyTest();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void DeathEvent();
};
