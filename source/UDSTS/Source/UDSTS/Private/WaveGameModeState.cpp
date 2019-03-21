// Fill out your copyright notice in the Description page of Project Settings.

#include "WaveGameModeState.h"
#include "SpawnUnit.h"
#include "SpawnUnitQueryInstanceWrapper.h"
#include "Kismet/GameplayStatics.h"
#include "UnitBase.h"
#include "SpawnUnitAsset.h"
#include "WaveDefenseGameState.h"
#include "UDSGameModeBase.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "EnvironmentQuery/EnvQueryManager.h"

void AWaveGameModeState::Init(FWaveLayout WaveLayout)
{
	CurrentWaveLayout = WaveLayout;

	SpawnUnits = WaveLayout.SpawnUnits;

	Algo::Sort(SpawnUnits, [](const auto su1, const auto su2)
	{
		return su1.TimeToSpawn <= su2.TimeToSpawn;
	});
}

void AWaveGameModeState::SpawnQueryFinished(TSharedPtr<FEnvQueryResult> Result)
{
	USpawnUnitAsset* spawnUnitAsset = Cast<USpawnUnitAsset>(Result->Owner);
	if (spawnUnitAsset == nullptr)
	{
		return;
	}

	TArray<FVector> locations;
	switch (Result->GetRawStatus())
	{
		case EEnvQueryStatus::Success:
			Result->GetAllAsLocations(locations);
			if (locations.Num() > 0)
			{
				FActorSpawnParameters SpawnInfo;
				SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
				AUnitBase* unit = GetWorld()->SpawnActor<AUnitBase>(spawnUnitAsset->UnitBase, locations[0], FRotator::ZeroRotator, SpawnInfo);
				if (unit != nullptr)
				{
					FVector origin, boxExtent;
					unit->GetActorBounds(false, origin, boxExtent);
					unit->AddActorWorldOffset(FVector(0, 0, boxExtent.Z));
					// TODO: Invoke ISpawnable (if this interface gets made)
					OnEnemyUnitSpawned.Broadcast(unit);
				}
			}
			break;
		default:
			break;
	}
}

void AWaveGameModeState::SpawnWithSpawnUnit(FSpawnUnit SpawnUnit)
{
	if (SpawnUnit.SpawnUnitAsset == nullptr)
	{
		return;
	}

	FEnvQueryRequest request = FEnvQueryRequest(SpawnQuery, SpawnUnit.SpawnUnitAsset);
	request.SetWorldOverride(GetWorld());
	request.Execute(EEnvQueryRunMode::RandomBest25Pct, this, &AWaveGameModeState::SpawnQueryFinished);
}

void AWaveGameModeState::OnStateEnter(AUDSGameModeBase* GameMode)
{
	CurrentSpawnUnitIndex = 0;
}

void AWaveGameModeState::OnStateStart(AUDSGameModeBase* GameMode)
{
	WaveClearedEvent.AddDynamic(GameMode, &AUDSGameModeBase::NextWave);
	OnEnemyUnitSpawned.AddDynamic(GameMode, &AUDSGameModeBase::HandleEnemySpawn);
}

void AWaveGameModeState::OnStateTick(AUDSGameModeBase* GameMode, const float DeltaTime)
{
	RunningTime += DeltaTime;

	if (CurrentSpawnUnitIndex < SpawnUnits.Num())
	{
		// there's still units left to spawn.
		if (RunningTime >= SpawnUnits[CurrentSpawnUnitIndex].TimeToSpawn)
		{
			SpawnWithSpawnUnit(SpawnUnits[CurrentSpawnUnitIndex]);
			CurrentSpawnUnitIndex++;
			if (CurrentSpawnUnitIndex >= SpawnUnits.Num())
			{
				WaveFinishSpawning.Broadcast();
			}
		}
	}
	else
	{
		// no more units left to spawn. Check for wave clear.
		AWaveDefenseGameState* gs = GameMode->GetGameState<AWaveDefenseGameState>();
		if (gs != nullptr)
		{
			if (gs->EnemiesLeft <= 0)
			{
				WaveClearedEvent.Broadcast();
			}
		}
	}

}

void AWaveGameModeState::OnStateStop(AUDSGameModeBase* GameMode)
{
	WaveClearedEvent.RemoveDynamic(GameMode, &AUDSGameModeBase::NextWave);
	OnEnemyUnitSpawned.RemoveDynamic(GameMode, &AUDSGameModeBase::HandleEnemySpawn);
}
