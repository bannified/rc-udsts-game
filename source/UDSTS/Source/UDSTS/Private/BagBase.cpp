// Fill out your copyright notice in the Description page of Project Settings.


#include "BagBase.h"
#include "UnrealNetwork.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"

// Sets default values
ABagBase::ABagBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SetRootComponent(SceneRoot);

	BagMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BagMesh"));
	BagMeshComponent->SetupAttachment(RootComponent);

	BagMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BagMeshComponent->SetCollisionObjectType(ECC_WorldDynamic);
	BagMeshComponent->SetCollisionResponseToAllChannels(ECR_Block);
	BagMeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECR_Overlap);

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(BagMeshComponent);
	AudioComponent->bAutoActivate = false;

	SetReplicates(true);
}

bool ABagBase::IsMatterSufficient(float value)
{
	return value <= Matter;
}

void ABagBase::PlayBoostSound_Implementation()
{
	AudioComponent->Sound = BoostSoundCue;
	AudioComponent->Play();
}

void ABagBase::ModifyMatterBy_Implementation(float deltaMatter, bool overflow /*= false*/)
{
	Matter += deltaMatter;
}

bool ABagBase::ModifyMatterBy_Validate(float deltaMatter, bool overflow /*= false*/)
{
	return true;
}

// Called when the game starts or when spawned
void ABagBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABagBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABagBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABagBase, Matter);
	DOREPLIFETIME(ABagBase, MaxMatter);
}

