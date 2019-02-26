// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthComponent.h"
#include "Engine.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::InitHealth(float startingHealth)
{
	currentHealth = startingHealth;
	isDead = false;
}

void UHealthComponent::TakeDamage(float damage)
{
	currentHealth -= damage;

	if (currentHealth >= 0.0f) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::SanitizeFloat(currentHealth));
	}
	else {
		//Dead
		currentHealth = 0.0f;
		isDead = true;
		DeathEvent.Broadcast();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Is dead (HealthComponent)"));
	}
}

