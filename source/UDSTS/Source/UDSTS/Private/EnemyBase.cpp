// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyBase.h"

// Sets default values
AEnemyBase::AEnemyBase() : AUnitBase()
{
	// Set this pawn to call Tick() every frame.  You can t urn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyBase::TakeDamage(float damage) {
	Super::HealthComponent->TakeDamage(damage);
}

void AEnemyBase::DeathEvent()
{
	Destroy();

	if (GEngine == nullptr)
	{
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Enemy is dead (EnemyTest)"));
}
