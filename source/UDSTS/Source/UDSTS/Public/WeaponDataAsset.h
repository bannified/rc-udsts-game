// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WeaponProperties.h"
#include "SlateBrush.h"
#include "WeaponDataAsset.generated.h"

class UStaticMesh;

/**
 * 
 */
UCLASS()
class UDSTS_API UWeaponDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Gameplay")
	FWeaponProperties m_Properties;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Gameplay")
	int32 MaxLevel;

	// TODO: Nozzle Class. UNozzleBase probably.

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Visual")
	UStaticMesh* Mesh;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Description")
	FName DisplayName;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Description")
	FSlateBrush DisplayImage;

};
