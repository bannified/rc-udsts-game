// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameModeState.generated.h"

class AUDSGameModeBase;

UCLASS(config = Game, notplaceable, BlueprintType, Blueprintable, Transient, hideCategories = (Info, Rendering, MovementReplication, Replication, Actor), meta = (ShortTooltip = "Game Mode State defines the logic being carried out by the Game Mode (as a State Machine)."))
class UDSTS_API AGameModeState : public AInfo
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, Category = "Gameplay Data")
		FName DisplayName;

	/**
	 * Called when the GameMode enters this state.
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Game Mode State")
		void OnStateEnter(AUDSGameModeBase* GameMode);

	/**
	 * Called whenever this states starts executing.
	 * Therefore, this method is called even when the GameMode is resumed (but still in this state).
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Game Mode State")
		void OnStateStart(AUDSGameModeBase* GameMode);

	/**
	 * Called every tick when this GameMode is active with this state.
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Game Mode State")
		void OnStateTick(AUDSGameModeBase* GameMode, float DeltaTime);

	/**
	 * Called when state stops.
	 * Therefore, this method is called even when the GameMode is paused (but still in this state).
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Game Mode State")
		void OnStateStop(AUDSGameModeBase* GameMode);

	/**
	 * Called when GameMode exits this state.
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Game Mode State")
		void OnStateExit(AUDSGameModeBase* GameMode);

};
