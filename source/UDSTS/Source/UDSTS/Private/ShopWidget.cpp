// Fill out your copyright notice in the Description page of Project Settings.

#include "ShopWidget.h"
#include "CharacterBase.h"
#include "Shop.h"
#include "PlayerControllerBase.h"

void UShopWidget::Setup(APlayerControllerBase* controller, AShop* shop)
{
	controller->OnUILeft.AddDynamic(this, &UShopWidget::OnLeftButton);
	controller->OnUIRight.AddDynamic(this, &UShopWidget::OnRightButton);
	controller->OnUIUp.AddDynamic(this, &UShopWidget::OnUpButton);
	controller->OnUIDown.AddDynamic(this, &UShopWidget::OnDownButton);

	controller->OnEscapeDown.AddDynamic(this, &UShopWidget::OnEscapeButton);
	controller->OnShopBuy.AddDynamic(this, &UShopWidget::OnShopBuy);
	
	ShopInstance = shop;
}

void UShopWidget::Shutdown(APlayerControllerBase* controller)
{
	controller->OnUILeft.RemoveDynamic(this, &UShopWidget::OnLeftButton);
	controller->OnUIRight.RemoveDynamic(this, &UShopWidget::OnRightButton);
	controller->OnUIUp.RemoveDynamic(this, &UShopWidget::OnUpButton);
	controller->OnUIDown.RemoveDynamic(this, &UShopWidget::OnDownButton);
}

bool UShopWidget::BuyWeapon(UWeaponDataAsset* weapon)
{
	ACharacterBase* character = ShopInstance->CurrentCharacter;

	int nextLevel = -1;

	int* currentLevel = character->GetWeaponCurrentLevel(weapon);

	if (currentLevel == nullptr) {
		nextLevel = 0;
	} 
	else {
		nextLevel = *currentLevel + 1;
	}

	if (nextLevel < 0 || nextLevel >= weapon->GetMaxLevel()) {
		// invalid level.
		return false;
	}

	// checking for price.
	FWeaponProperties properties = weapon->PropertiesList[nextLevel];

	if (character->GetCurrentMatter() < properties.CostOfUpgrade) {
		// not enough money.
		return false;
	}

	ShopInstance->BuyWeaponForCharacter(weapon, character);

	return true;
}

void UShopWidget::OnLeftButton(APlayerControllerBase* controller)
{
	OnLeftButtonReceive.Broadcast(controller);
}

void UShopWidget::OnRightButton(APlayerControllerBase* controller)
{
	OnRightButtonReceive.Broadcast(controller);
}

void UShopWidget::OnDownButton(APlayerControllerBase* controller)
{
	OnDownButtonReceive.Broadcast(controller);
}

void UShopWidget::OnUpButton(APlayerControllerBase* controller)
{
	OnUpButtonReceive.Broadcast(controller);
}

void UShopWidget::OnEscapeButton(APlayerControllerBase* controller)
{
	OnEscapeButtonReceive.Broadcast(controller);
}

void UShopWidget::OnShopBuy(APlayerControllerBase* controller)
{
	OnShopBuyReceive.Broadcast(controller);
}
