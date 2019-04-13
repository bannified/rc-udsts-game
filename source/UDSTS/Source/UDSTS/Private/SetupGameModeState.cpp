// Fill out your copyright notice in the Description page of Project Settings.

#include "SetupGameModeState.h"
#include "WaveLayout.h"
#include "WaveGameModeState.h"
#include "UDSGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void ASetupGameModeState::Init(FWaveLayout WaveLayout, TSubclassOf<AWaveGameModeState> WaveGameModeStateClass)
{
	RunningTime = 0;
	UpcomingWave = WaveLayout;
	SetupTime = UpcomingWave.SetupTime;
	SkipButton = FKey(FName("SpaceBar"));
	fastFoward = false;
}

void ASetupGameModeState::OnStateTick(AUDSGameModeBase* GameMode, const float DeltaTime)
{
	RunningTime += DeltaTime;

	if (RunningTime >= SetupTime || fastFoward)
	{
		TransitionToWave(GameMode);
	}

	ReceiveOnStateTick(GameMode, DeltaTime);
}

void ASetupGameModeState::OnStateExit(AUDSGameModeBase* GameMode)
{

	ReceiveOnStateExit(GameMode);

	Destroy();
}

void ASetupGameModeState::TransitionToWave(AUDSGameModeBase* GameMode)
{
	FActorSpawnParameters SpawnInfo;
	AWaveGameModeState* waveState = GetWorld()->SpawnActor<AWaveGameModeState>(WaveGameModeStateClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);

	waveState->Init(UpcomingWave);

	GameMode->MoveToState(waveState);
}
