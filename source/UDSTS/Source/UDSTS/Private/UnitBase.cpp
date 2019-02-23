// Fill out your copyright notice in the Description page of Project Settings.

#include "UnitBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/MeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "AIModule/Classes/AIController.h"
#include "Components/CapsuleComponent.h"
//#include "Blueprint/AIBlueprintHelperLibrary.h"

// Sets default values
AUnitBase::AUnitBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*MainCollider = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MainCollider"));
	SetRootComponent(MainCollider);

	MainCollider->SetCanEverAffectNavigation(false);
	MainCollider->SetCollisionObjectType(ECC_WorldDynamic);
	MainCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MainCollider->SetCollisionProfileName(FName("BlockAllDynamic"));*/

	MainMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MainMesh"));
	SetRootComponent(MainMesh);

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

	SetReplicateMovement(true);
}

// Called when the game starts or when spawned
void AUnitBase::BeginPlay()
{
	Super::BeginPlay();

	/*AAIController* aiController = UAIBlueprintHelperLibrary::GetAIController(this);

	if (UnitBehaviorTree_Asset != nullptr && aiController != nullptr)
	{
		UAIBlueprintHelperLibrary::GetAIController(this)->RunBehaviorTree(UnitBehaviorTree_Asset);
	}*/

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

