// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameModeState.generated.h"

class AUDSGameModeBase;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGameModeState : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UDSTS_API IGameModeState
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
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
