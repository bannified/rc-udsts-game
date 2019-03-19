// Fill out your copyright notice in the Description page of Project Settings.

#include "GameModeState.h"

void AGameModeState::OnStateEnter(AUDSGameModeBase* GameMode)
{
	ReceiveOnStateEnter(GameMode);
}

void AGameModeState::OnStateStart(AUDSGameModeBase* GameMode)
{
	ReceiveOnStateStart(GameMode);
}

void AGameModeState::OnStateTick(AUDSGameModeBase* GameMode, float DeltaTime)
{
	ReceiveOnStateTick(GameMode, DeltaTime);
}

void AGameModeState::OnStateStop(AUDSGameModeBase* GameMode)
{
	ReceiveOnStateStop(GameMode);
}

void AGameModeState::OnStateExit(AUDSGameModeBase* GameMode)
{
	ReceiveOnStateExit(GameMode);
}
