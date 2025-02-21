// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "UnitBase.generated.h"

class USkeletalMeshComponent;
class UCapsuleComponent;
class UFloatingPawnMovement;
class UBehaviorTree;
class UMeshComponent;
class UHealthComponent;
class USpawnUnitAsset;

UCLASS()
class UDSTS_API AUnitBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AUnitBase();

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Components")
	UHealthComponent* HealthComponent;

protected:

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components")
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category = "Components")
	USkeletalMeshComponent* MainMesh;

	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Components")
	UFloatingPawnMovement* FloatingPawnMovement;	

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* UnitBehaviorTreeAsset;	

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gameplay")
	float MovementSpeed;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	USpawnUnitAsset* SpawnUnitAsset;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
