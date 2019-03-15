// Fill out your copyright notice in the Description page of Project Settings.

#include "UDSGameModeBase.h"
#include "SpawnPoint.h"
#include "Kismet/GameplayStatics.h"

void AUDSGameModeBase::SetupSpawnPointGroups()
{
	TArray<AActor*> spawnPoints;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnPoint::StaticClass(), spawnPoints);

	if (spawnPoints.Num() == 0)
	{
		return;
	}

	for (auto s : spawnPoints)
	{
		ASpawnPoint* spawnPoint = Cast<ASpawnPoint>(s);

		for (int number : spawnPoint->GroupNumbers)
		{
			// Resize SpawnPointGroups
			if (number >= (SpawnPointsGroups.Num()))
			{
				SpawnPointsGroups.SetNum(number + 1);
			}

			SpawnPointsGroups[number].arr.Add(spawnPoint);
		}
	}
}
