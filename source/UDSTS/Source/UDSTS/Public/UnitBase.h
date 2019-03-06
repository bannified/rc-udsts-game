// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "UnitBase.generated.h"

class USkeletalMeshComponent;
class UFloatingPawnMovement;
class UBehaviorTree;
class UMeshComponent;
class UHealthComponent;

UCLASS()
class UDSTS_API AUnitBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AUnitBase();

protected:

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	USkeletalMeshComponent* MainMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UFloatingPawnMovement* FloatingPawnMovement;

	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* UnitBehaviorTreeAsset;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
