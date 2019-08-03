// Fill out your copyright notice in the Description page of Project Settings.

#include "Shop.h"
#include "Components/BoxComponent.h"
#include "CharacterBase.h"
#include "PlayerControllerBase.h"
#include "NavigationSystem/Public/NavAreas/NavArea_Obstacle.h"
#include "ShopWidget.h"
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

	m_PlayerWithinBounds = false;

	EntryBox->OnComponentBeginOverlap.AddDynamic(this, &AShop::ActorEnter);
	ExitBox->OnComponentEndOverlap.AddDynamic(this, &AShop::ActorExit);
}

void AShop::ShowInteractWidget(APlayerControllerBase* controller)
{
	if (InteractWidgetInstance != nullptr) {
		return;
	}

	UUserWidget* instance = CreateWidget<UUserWidget, APlayerControllerBase>(controller, InteractWidgetClass);
	instance->AddToPlayerScreen(10);
	InteractWidgetInstance = instance;

	controller->OnInteractStart.AddDynamic(this, &AShop::ShowShopWidget);
}

void AShop::HideInteractWidget(APlayerControllerBase* controller)
{
	if (InteractWidgetInstance == nullptr) {
		return;
	}

	InteractWidgetInstance->RemoveFromParent();
	InteractWidgetInstance = nullptr;

	controller->OnInteractStart.RemoveDynamic(this, &AShop::ShowShopWidget);
}

void AShop::ShowShopWidget(APlayerControllerBase* controller)
{
	if (controller == nullptr) {
		return;
	}

	if (ShopWidgetInstance != nullptr) {
		return;
	}

	HideInteractWidget(controller);

	controller->OnInteractStart.AddDynamic(this, &AShop::HideShopWidget);

	UShopWidget* instance = CreateWidget<UShopWidget, APlayerControllerBase>(controller, ShopWidgetClass);
	instance->Setup(controller, this);
	instance->AddToPlayerScreen(10);
	ShopWidgetInstance = instance;
}

void AShop::HideShopWidget(APlayerControllerBase* controller)
{
	if (controller == nullptr) {
		return;
	}

	if (ShopWidgetInstance == nullptr) {
		return;
	}

	controller->OnInteractStart.RemoveDynamic(this, &AShop::HideShopWidget);

	ShopWidgetInstance->RemoveFromParent();
	ShopWidgetInstance = nullptr;

	if (m_PlayerWithinBounds) {
		ShowInteractWidget(controller);
	}
}

void AShop::ActorEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacterBase* character = Cast<ACharacterBase>(OtherActor);

	if (character == nullptr) {
		return;
	}

	// only looking out for local player.
	if (!character->IsLocallyControlled()) {
		return;
	}

	m_PlayerWithinBounds = true;

	APlayerControllerBase* controller = character->GetPlayerControllerBase();

	ShowInteractWidget(controller);
}

void AShop::ActorExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ACharacterBase* character = Cast<ACharacterBase>(OtherActor);

	if (character == nullptr) {
		return;
	}

	// only looking out for local player.
	if (!character->IsLocallyControlled()) {
		return;
	}

	m_PlayerWithinBounds = false;

	APlayerControllerBase* controller = character->GetPlayerControllerBase();

	HideInteractWidget(controller);
	HideShopWidget(controller);
}

void AShop::BuyWeaponForCharacter_Implementation(UWeaponDataAsset* weapon, ACharacterBase* character)
{
	character->UpgradeWeapon(weapon);

	character->SetWeapon(weapon);
}

bool AShop::BuyWeaponForCharacter_Validate(UWeaponDataAsset* weapon, ACharacterBase* character)
{
	int nextLevel = -1;

	const int* currentLevel = character->GetWeaponCurrentLevel(weapon);

	if (currentLevel == nullptr) {
		nextLevel = 0;
	}
	else {
		nextLevel = *currentLevel + 1;
	}

	if (nextLevel < 0 || nextLevel >= weapon->GetMaxLevel()) {
		// invalid level.
		return false;
	}

	// checking for price.
	FWeaponProperties properties = weapon->PropertiesList[nextLevel];

	if (character->GetCurrentMatter() < properties.CostOfUpgrade) {
		// not enough money.
		return false;
	}

	return true;
}

// Called every frame
void AShop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShop::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AShop, CurrentCharacter);
	DOREPLIFETIME(AShop, WeaponsList);
}
