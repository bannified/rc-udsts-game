// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterBase.h"
#include "WeaponDataAsset.h"

bool UWeaponDataAsset::IsBuyableByCharacter(ACharacterBase* character)
{
	const int* currentLevel = character->GetWeaponCurrentLevel(this);
	return true;
}
