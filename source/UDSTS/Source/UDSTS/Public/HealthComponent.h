// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeathEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UDSTS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	UPROPERTY(VisibleAnywhere)
	float currentHealth;
	UPROPERTY(VisibleAnywhere)
	bool isDead;
	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FDeathEvent DeathEvent;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Initialize health with specified value
	UFUNCTION()
	void InitHealth(float startingHealth);
	//Apply damage to unit
	UFUNCTION()
	void TakeDamage(float damage);
		
};
