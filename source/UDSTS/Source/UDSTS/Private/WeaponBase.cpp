// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "NozzleBase.h"
#include "WeaponDataAsset.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/AudioComponent.h"
#include "UnrealNetwork.h"


// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SetRootComponent(SceneRoot);

	WeaponMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	WeaponMeshComponent->SetupAttachment(RootComponent);

	WeaponMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponMeshComponent->SetCollisionObjectType(ECC_WorldStatic);
	WeaponMeshComponent->SetWorldRotation(FRotator(0.0, 90.0f, 0.0f));

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(RootComponent);
}

void AWeaponBase::StopPrimarySound_Implementation()
{

}

void AWeaponBase::PlaySecondarySound_Implementation()
{

}

void AWeaponBase::PlayPrimarySound_Implementation()
{

}

float AWeaponBase::ConvertRawMatterToFinalMatter(float inMatter)
{
	return 0.0f;
}

void AWeaponBase::InitNozzle_Implementation(ANozzleBase* Nozzle, UWeaponDataAsset* nozzleData)
{

}

bool AWeaponBase::InitNozzle_Validate(ANozzleBase* Nozzle, UWeaponDataAsset* nozzleData)
{
	return true;
}

void AWeaponBase::SetNozzleProperties_Implementation(UWeaponDataAsset* nozzleData, int level)
{

}

bool AWeaponBase::SetNozzleProperties_Validate(UWeaponDataAsset* nozzleData, int level)
{
	return true;
}

void AWeaponBase::SecondaryEnd_Implementation()
{

}

bool AWeaponBase::SecondaryEnd_Validate()
{
	return true;
}

void AWeaponBase::SecondaryUpdate_Implementation()
{

}

bool AWeaponBase::SecondaryUpdate_Validate()
{
	return true;
}

void AWeaponBase::SecondaryStart_Implementation()
{

}

bool AWeaponBase::SecondaryStart_Validate()
{
	return true;
}

void AWeaponBase::PrimaryEnd_Implementation()
{

}

bool AWeaponBase::PrimaryEnd_Validate()
{
	return true;
}

void AWeaponBase::PrimaryUpdate_Implementation()
{

}

bool AWeaponBase::PrimaryUpdate_Validate()
{
	return true;
}

void AWeaponBase::PrimaryStart_Implementation()
{

}

bool AWeaponBase::PrimaryStart_Validate()
{
	return true;
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AWeaponBase, CurrentNozzle);
	DOREPLIFETIME(AWeaponBase, Character);

}

