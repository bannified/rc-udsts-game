// Fill out your copyright notice in the Description page of Project Settings.

#include "Shop.h"
#include "Components/BoxComponent.h"
#include "CharacterBase.h"
#include "PlayerControllerBase.h"
#include "NavigationSystem/Public/NavAreas/NavArea_Obstacle.h"
#include "UserWidget.h"
#include "UDSTS.h"

// Sets default values
AShop::AShop()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(FName("RootSceneComponent"));
	RootComponent = RootSceneComponent;

	EntryBox = CreateDefaultSubobject<UBoxComponent>(FName("EntryBox"));
	EntryBox->SetupAttachment(RootComponent);

	EntryBox->SetRelativeLocation(FVector(0, 0, 0));
	EntryBox->SetRelativeScale3D(FVector(2.0, 2.0, 1.5));
	EntryBox->SetMobility(EComponentMobility::Stationary);
	EntryBox->SetBoxExtent(FVector(50.0, 50.0, 60.0));
	EntryBox->AreaClass = UNavArea_Obstacle::StaticClass();

	EntryBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	EntryBox->SetCollisionObjectType(COLLISION_WATER);
	EntryBox->SetCollisionResponseToAllChannels(ECR_Overlap);
	EntryBox->SetCollisionResponseToChannel(COLLISION_WATER, ECR_Ignore);
	EntryBox->SetCollisionResponseToChannel(COLLISION_BASE, ECR_Block);

	ExitBox = CreateDefaultSubobject<UBoxComponent>(FName("ExitBox"));
	ExitBox->SetupAttachment(RootComponent);

	ExitBox->SetRelativeLocation(FVector(0, 0, 0));
	ExitBox->SetRelativeScale3D(FVector(1.25, 1.5, 1.25));
	ExitBox->SetMobility(EComponentMobility::Stationary);
	ExitBox->SetBoxExtent(FVector(100.0, 100.0, 100.0));
	ExitBox->AreaClass = UNavArea_Obstacle::StaticClass();

	ExitBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ExitBox->SetCollisionObjectType(COLLISION_WATER);
	ExitBox->SetCollisionResponseToAllChannels(ECR_Overlap);
	ExitBox->SetCollisionResponseToChannel(COLLISION_WATER, ECR_Ignore);
	ExitBox->SetCollisionResponseToChannel(COLLISION_BASE, ECR_Block);

}

// Called when the game starts or when spawned
void AShop::BeginPlay()
{
	Super::BeginPlay();

	EntryBox->OnComponentBeginOverlap.AddDynamic(this, &AShop::ShowInteractWidget);
	ExitBox->OnComponentEndOverlap.AddDynamic(this, &AShop::HideInteractWidget);
}

void AShop::ShowInteractWidget(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacterBase* character = Cast<ACharacterBase>(OtherActor);

	if (character == nullptr) {
		return;
	}

	if (!character->IsLocallyControlled()) {
		return;
	}

	UUserWidget* instance = CreateWidget<UUserWidget, APlayerControllerBase>(character->GetPlayerControllerBase(), InteractWidgetClass);
	instance->AddToPlayerScreen(10);
	InteractWidgetInstance = instance;
}

void AShop::HideInteractWidget(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ACharacterBase* character = Cast<ACharacterBase>(OtherActor);

	if (character == nullptr) {
		return;
	}

	if (!character->IsLocallyControlled()) {
		return;
	}

	if (InteractWidgetInstance == nullptr) {
		return;
	}

	InteractWidgetInstance->RemoveFromParent();
	InteractWidgetInstance = nullptr;
}

// Called every frame
void AShop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

