// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShopWidget.generated.h"

class ACharacterBase;

/**
 * 
 */
UCLASS()
class UDSTS_API UShopWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetupWithCharacter(APlayerControllerBase* character);

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void PreviousItemPressed(APlayerControllerBase* character);

	UFUNCTION(BlueprintImplementableEvent)
	void NextItemPressed(APlayerControllerBase* character);

};
