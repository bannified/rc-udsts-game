// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyTest.h"
#include "Engine.h"
#include "HealthComponent.h"

// Sets default values
AEnemyTest::AEnemyTest()
{
	// Set this pawn to call Tick() every frame.  You can t urn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Super::Super::HealthComponent->InitHealth(100.0f);
	Super::movementSpeed = 100.0f;
	Super::matter = 100.0f;

	//Bind this deathevent with healthcomponent DeathEvent broadcast/calls
	Super::Super::HealthComponent->DeathEvent.AddDynamic(this, &AEnemyTest::DeathEvent);
}

// Called every frame
void AEnemyTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Super::TakeDamage(5.0f);
}

void AEnemyTest::DeathEvent() {
	Destroy();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Enemy is dead (EnemyTest)"));
}

