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
	USpawnUnitAsset* spawnUnit = Cast<USpawnUnitAsset>(Result->Owner);
	if (spawnUnit == nullptr)
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
				SpawnWithSpawnUnitAssetAtLocation(spawnUnit, locations[0]);
			}
			break;
		default:
			break;
	}
}

void AWaveGameModeState::SpawnWithSpawnUnit(AUDSGameModeBase* GameMode, FSpawnUnit SpawnUnit)
{
	if (SpawnUnit.SpawnUnitAsset == nullptr)
	{
		return;
	}

	GameMode->NextSpawnUnit = SpawnUnit;

	FEnvQueryRequest request = FEnvQueryRequest(SpawnQuery, SpawnUnit.SpawnUnitAsset);
	request.SetWorldOverride(GetWorld());
	request.Execute(EEnvQueryRunMode::RandomBest25Pct, this, &AWaveGameModeState::SpawnQueryFinished);
}

AUnitBase* AWaveGameModeState::SpawnWithSpawnUnitAssetAtLocation(USpawnUnitAsset* SpawnUnitAsset, const FVector location)
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	if (SpawnUnitAsset == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("SpawnUnitAsset == nullptr"));
		return nullptr;
	}

	AUnitBase* unit = GetWorld()->SpawnActor<AUnitBase>(SpawnUnitAsset->UnitBase, location, FRotator::ZeroRotator, SpawnInfo);
	if (unit != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("After unit spawning."));
		FVector origin, boxExtent;
		unit->GetActorBounds(false, origin, boxExtent);
		unit->AddActorWorldOffset(FVector(0, 0, boxExtent.Z));
		unit->SpawnUnitAsset = SpawnUnitAsset;
		UE_LOG(LogTemp, Warning, TEXT("Before InitializeUnit"));
		SpawnUnitAsset->InitializeUnit(unit);
		// TODO: Invoke ISpawnable (if this interface gets made)
		OnEnemyUnitSpawned.Broadcast(unit);

		return unit;
	}
	UE_LOG(LogTemp, Warning, TEXT("End of Spawn"));
	return nullptr;
}

void AWaveGameModeState::OnStateEnter(AUDSGameModeBase* GameMode)
{
	CurrentSpawnUnitIndex = 0;
	ReceiveOnStateEnter(GameMode);
}

void AWaveGameModeState::OnStateStart(AUDSGameModeBase* GameMode)
{
	//WaveClearedEvent.AddDynamic(GameMode, &AUDSGameModeBase::NextWave);
	OnEnemyUnitSpawned.AddDynamic(GameMode, &AUDSGameModeBase::HandleEnemySpawn);

	ReceiveOnStateStart(GameMode);
}

void AWaveGameModeState::OnStateTick(AUDSGameModeBase* GameMode, const float DeltaTime)
{
	RunningTime += DeltaTime;

	if (CurrentSpawnUnitIndex < SpawnUnits.Num())
	{
		// there's still units left to spawn.
		if (RunningTime >= SpawnUnits[CurrentSpawnUnitIndex].TimeToSpawn)
		{
			SpawnWithSpawnUnit(GameMode, SpawnUnits[CurrentSpawnUnitIndex]);
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

	ReceiveOnStateTick(GameMode, DeltaTime);
}

void AWaveGameModeState::OnStateStop(AUDSGameModeBase* GameMode)
{
	//WaveClearedEvent.RemoveDynamic(GameMode, &AUDSGameModeBase::NextWave);
	OnEnemyUnitSpawned.RemoveDynamic(GameMode, &AUDSGameModeBase::HandleEnemySpawn);

	ReceiveOnStateStop(GameMode);
}

void AWaveGameModeState::OnStateExit(AUDSGameModeBase* GameMode)
{
	GameMode->OnWaveCleared.Broadcast();
	ReceiveOnStateExit(GameMode);
	Destroy();
}
