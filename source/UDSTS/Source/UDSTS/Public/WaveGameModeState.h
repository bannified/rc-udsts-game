// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameModeState.h"
#include "WaveLayout.h"
#include "WaveGameModeState.generated.h"

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

};
