// Fill out your copyright notice in the Description page of Project Settings.

#include "UDSGameModeBase.h"
#include "SpawnPoint.h"
#include "GameModeState.h"
#include "LevelDataAsset.h"
#include "Base.h"
#include "HealthComponent.h"
#include "Blueprint/UserWidget.h"
#include "WaveDefenseGameState.h"
#include "SetupGameModeState.h"
#include "EnemyBase.h"
#include "Kismet/GameplayStatics.h"

void AUDSGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	SetupSpawnPointGroups();

	AWaveDefenseGameState* gs = GetGameState<AWaveDefenseGameState>();

	TArray<AActor*> baseArr;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABase::StaticClass(), baseArr);
	
	if (baseArr.Num() > 0)
	{
		ABase* base = Cast<ABase>(baseArr[0]);
		if (base)
		{
			base->HealthComponent->DeathEvent.AddDynamic(this, &AUDSGameModeBase::LoseGame);
			if (gs)
			{
				gs->BaseOfInterest = base;
			}
		}
	}

	PrimaryActorTick.bCanEverTick = true;

}

void AUDSGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentState != nullptr)
	{
		CurrentState->OnStateTick(this, DeltaTime);
	}

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

AUDSGameModeBase::AUDSGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AUDSGameModeBase::MoveToState(AGameModeState* NextState)
{
	AGameModeState* oldState = CurrentState;

	if (CurrentState != nullptr)
	{
		CurrentState->OnStateStop(this);
		CurrentState->OnStateExit(this);
	}	

	if (NextState != nullptr)
	{
		CurrentState = NextState;

		NextState->OnStateEnter(this);
		NextState->OnStateStart(this);
	}

	OnStateChanged.Broadcast(oldState, CurrentState);
}

void AUDSGameModeBase::StartGame(ULevelDataAsset* LevelData)
{
	AWaveDefenseGameState* gs = GetGameState<AWaveDefenseGameState>();

	TArray<AActor*> baseArr;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABase::StaticClass(), baseArr);

	if (baseArr.Num() > 0)
	{
		ABase* base = Cast<ABase>(baseArr[0]);
		if (base)
		{
			gs->BaseOfInterest = base;
		}
	}

	if (GameHUDWidget != nullptr)
	{
		UUserWidget* hudWidget = CreateWidget(GetWorld()->GetFirstPlayerController(), GameHUDWidget);

		hudWidget->AddToViewport();
	}

	/*if (MapLevelDataAsset == nullptr)
	{
		if (FallbackLevelData != nullptr)
		{
			MapLevelDataAsset = FallbackLevelData;
		}
		else
		{
			return;
		}
	}*/

	MapLevelDataAsset = LevelData;

	// Spawn Setup State
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Owner = this;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	ASetupGameModeState* setupState = GetWorld()->SpawnActor<ASetupGameModeState>(SetupGameModeStateClass, FVector::ZeroVector, FRotator::ZeroRotator);

	setupState->Init(MapLevelDataAsset->Waves[CurrentWaveIndex], WaveGameModeStateClass);

	// Move to SetupState
	MoveToState(setupState);
}

void AUDSGameModeBase::NextWave()
{
	CurrentWaveIndex++;

	TArray<FWaveLayout> waves = MapLevelDataAsset->Waves;

	if (CurrentWaveIndex < waves.Num())
	{
		// Spawn Setup State
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.Owner = this;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		ASetupGameModeState* setupState = GetWorld()->SpawnActor<ASetupGameModeState>(SetupGameModeStateClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);

		setupState->Init(MapLevelDataAsset->Waves[CurrentWaveIndex], WaveGameModeStateClass);

		MoveToState(setupState);
	}
	else
	{
		// TODO: no more levels left, Win!
		WinGame();
	}
}

void AUDSGameModeBase::WinGame()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Win Game!"));

	OnGameWin.Broadcast();
}

void AUDSGameModeBase::LoseGame()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Lose Game!"));

	OnGameLose.Broadcast();
}

void AUDSGameModeBase::OnEnemyDestroyed(AActor* EnemyDestroyed)
{
	AWaveDefenseGameState* gs = GetGameState<AWaveDefenseGameState>();

	gs->EnemiesLeft--;

	EnemyDestroyed->OnDestroyed.RemoveDynamic(this, &AUDSGameModeBase::OnEnemyDestroyed);
}

void AUDSGameModeBase::HandleEnemySpawn(AActor* SpawnedEnemy)
{
	AWaveDefenseGameState* gs = GetGameState<AWaveDefenseGameState>();

	SpawnedEnemy->OnDestroyed.AddDynamic(this, &AUDSGameModeBase::OnEnemyDestroyed);

	gs->EnemiesLeft++;
}
