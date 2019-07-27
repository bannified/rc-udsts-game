// Fill out your copyright notice in the Description page of Project Settings.

#include "WaveDefenseGameState.h"
#include "PlayerControllerBase.h"
#include "GameFramework/PlayerState.h"

void AWaveDefenseGameState::AddPlayerState(APlayerState* playerState)
{
	if (!playerState->bIsInactive) 
	{
		PlayerArray.AddUnique(playerState);
	}
}
