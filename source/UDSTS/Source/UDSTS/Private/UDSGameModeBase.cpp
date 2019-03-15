// Fill out your copyright notice in the Description page of Project Settings.

#include "UDSGameModeBase.h"
#include "SpawnPoint.h"
#include "Kismet/GameplayStatics.h"

void AUDSGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	SetupSpawnPointGroups();

}

void AUDSGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}

void AUDSGameModeBase::SetupSpawnPointGroups()
{
	TArray<AActor*> spawnPoints;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnPoint::StaticClass(), spawnPoints);

	if (spawnPoints.Num() == 0)
	{
		return;
	}

	SpawnPointsGroups.Add(FSpawnPointArray());

	for (auto s : spawnPoints)
	{
		ASpawnPoint* spawnPoint = Cast<ASpawnPoint>(s);

		SpawnPointsGroups[0].arr.Add(spawnPoint);

		for (int number : spawnPoint->GroupNumbers)
		{
			if (number == 0)
			{
				continue;
			}
			// Resize SpawnPointGroups
			if (number >= (SpawnPointsGroups.Num()))
			{
				SpawnPointsGroups.SetNum(number + 1);
			}

			SpawnPointsGroups[number].arr.Add(spawnPoint);
		}
	}
}

void AUDSGameModeBase::SpawnWithSpawnUnit(const FSpawnUnit spawnUnit)
{

}
