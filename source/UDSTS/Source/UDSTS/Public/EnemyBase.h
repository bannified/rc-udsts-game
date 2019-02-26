// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HealthComponent.h"
#include "UnitBase.h"
#include "EnemyBase.generated.h"

/**
 * 
 */
UCLASS()
class UDSTS_API AEnemyBase : public AUnitBase
{
	GENERATED_BODY()
	
public:
	// Sets default values for this pawn's properties
	AEnemyBase();

	UPROPERTY(VisibleAnywhere)
		float movementSpeed;
	UPROPERTY(VisibleAnywhere)
		float matter;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void TakeDamage(float damage);


};
