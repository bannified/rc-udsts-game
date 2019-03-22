// Fill out your copyright notice in the Description page of Project Settings.

#include "UnitBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/MeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "AIModule/Classes/AIController.h"
#include "Components/CapsuleComponent.h"
#include "HealthComponent.h"
//#include "Blueprint/AIBlueprintHelperLibrary.h"

// Sets default values
AUnitBase::AUnitBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComponent->SetCanEverAffectNavigation(false);
	CapsuleComponent->SetCollisionObjectType(ECC_WorldDynamic);
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CapsuleComponent->SetCollisionProfileName(FName("BlockAllDynamic"));

	SetRootComponent(CapsuleComponent);

	MainMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MainMesh"));
	MainMesh->SetupAttachment(CapsuleComponent);

	MainMesh->SetCanEverAffectNavigation(false);
	MainMesh->SetCollisionObjectType(ECC_WorldDynamic);
	MainMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MainMesh->SetCollisionProfileName(FName("BlockAllDynamic"));

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));
	FloatingPawnMovement->NavAgentProps.bCanSwim = true;
	FloatingPawnMovement->MaxSpeed = 300.0f;
	FloatingPawnMovement->Acceleration = 2500.0f;
	FloatingPawnMovement->Deceleration = 8000.0f;
	FloatingPawnMovement->TurningBoost = 1.0f;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	SetReplicateMovement(true);
}

// Called when the game starts or when spawned
void AUnitBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AUnitBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AUnitBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

