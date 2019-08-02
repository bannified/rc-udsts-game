// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShopWidget.generated.h"

class ACharacterBase;
class APlayerControllerBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerInputEvent, APlayerControllerBase*, controller);

/**
 * 
 */
UCLASS()
class UDSTS_API UShopWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void Setup(APlayerControllerBase* controller);
	void Shutdown(APlayerControllerBase* controller);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
	void BuyNozzle();

protected:

	UPROPERTY(BlueprintAssignable, Category = "UI Events")
	FPlayerInputEvent OnLeftButtonReceive;
	UPROPERTY(BlueprintAssignable, Category = "UI Events")
	FPlayerInputEvent OnRightButtonReceive;
	UPROPERTY(BlueprintAssignable, Category = "UI Events")
	FPlayerInputEvent OnUpButtonReceive;
	UPROPERTY(BlueprintAssignable, Category = "UI Events")
	FPlayerInputEvent OnDownButtonReceive;
	UPROPERTY(BlueprintAssignable, Category = "UI Events")
	FPlayerInputEvent OnEscapeButtonReceive;
	UPROPERTY(BlueprintAssignable, Category = "UI Events")
	FPlayerInputEvent OnShopBuyReceive;

private:

	void OnLeftButton(APlayerControllerBase* controller);
	void OnRightButton(APlayerControllerBase* controller);
	void OnDownButton(APlayerControllerBase* controller);
	void OnUpButton(APlayerControllerBase* controller);

	void OnEscapeButton(APlayerControllerBase* controller);

	void OnShopBuy(APlayerControllerBase* controller);
};
