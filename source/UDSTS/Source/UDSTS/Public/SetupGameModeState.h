// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WaveLayout.h"
#include "GameModeState.h"
#include "SetupGameModeState.generated.h"

class AUDSGameModeBase;

/**
 * 
 */
UCLASS()
class UDSTS_API ASetupGameModeState : public AGameModeState
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gameplay")
	FKey SkipButton;

	UFUNCTION(BlueprintCallable, Category = "StateMachine")
	void Init(FWaveLayout WaveLayout);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	float RunningTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	float SetupTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	FWaveLayout UpcomingWave;

	virtual void OnStateTick(AUDSGameModeBase* GameMode, const float DeltaTime) override;

	virtual void OnStateExit(AUDSGameModeBase* GameMode) override;

protected:
	UFUNCTION(BlueprintCallable, Category = "StateMachine")
	void TransitionToWave(AUDSGameModeBase* GameMode);
};
