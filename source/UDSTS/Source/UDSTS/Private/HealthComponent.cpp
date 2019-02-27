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


void UHealthComponent::HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f || bIsDead)
		return;

	// avoid friendly fire
	if (DamageCauser != DamagedActor) //&& IsFriendly(DamagedActor, DamageCauser))
	{
		return;
	}

	currentHealth = FMath::Clamp(currentHealth - Damage, 0.0f, maxHealth);

	// FString converts to a char[], which is required by the TEXT
	UE_LOG(LogTemp, Log, TEXT("Health changed: %s"), *FString::SanitizeFloat(currentHealth));

	OnHealthChanged.Broadcast(this, currentHealth, Damage, DamageType, InstigatedBy, DamageCauser);

	bIsDead = currentHealth <= 0.0f;

	if (bIsDead)
	{
		DeathEvent.Broadcast();
	}

	// Networking code
	//if (bIsDead)
	//{
	//	// this block will only run on server already anyway, since only server had Game Mode.
	//	// but this if statement is just to cut off useless calls.
	//	if (GetOwnerRole() == ROLE_Authority)
	//	{
	//		ASGameMode* gm = Cast<ASGameMode>(GetWorld()->GetAuthGameMode());
	//		if (gm)
	//		{
	//			gm->OnActorKilled.Broadcast(GetOwner(), DamageCauser, InstigatedBy);
	//		}
	//	}
	//}
}

float UHealthComponent::GetHealth() const
{
	return currentHealth;
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::InitHealth(float health)
{
	currentHealth = startingHealth;
	bIsDead = false;
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
		bIsDead = true;
		DeathEvent.Broadcast();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Is dead (HealthComponent)"));
	}
}

void UHealthComponent::AlterHealth(float Amount)
{
	// already dead
	if (currentHealth <= 0)
		return;

	currentHealth = FMath::Clamp(currentHealth + Amount, 0.0f, maxHealth);

	UE_LOG(LogTemp, Log, TEXT("Health changed: %s (+%s)"), *FString::SanitizeFloat(currentHealth), *FString::SanitizeFloat(Amount));

	OnHealthChanged.Broadcast(this, currentHealth, -Amount, nullptr, nullptr, nullptr);
}

