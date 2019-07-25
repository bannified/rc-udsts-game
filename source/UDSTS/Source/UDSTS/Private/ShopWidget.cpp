// Fill out your copyright notice in the Description page of Project Settings.

#include "ShopWidget.h"
#include "CharacterBase.h"
#include "PlayerControllerBase.h"

void UShopWidget::SetupWithCharacter(APlayerControllerBase* controller)
{
	controller->OnPreviousEquipment.AddDynamic(this, &UShopWidget::PreviousItemPressed);
	controller->OnNextEquipment.AddDynamic(this, &UShopWidget::NextItemPressed);
}
