// Fill out your copyright notice in the Description page of Project Settings.

#include "Shop.h"
#include "Components/BoxComponent.h"
#include "CharacterBase.h"
#include "PlayerControllerBase.h"
#include "UserWidget.h"

// Sets default values
AShop::AShop()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

	UUserWidget* instance = CreateWidget<UUserWidget, APlayerControllerBase>(character->GetPlayerControllerBase(), InteractWidgetClass);
	instance->AddToPlayerScreen(10);
	character->ContextualWidget = instance;
}

void AShop::HideInteractWidget(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ACharacterBase* character = Cast<ACharacterBase>(OtherActor);

	if (character == nullptr) {
		return;
	}

	if (character->ContextualWidget != nullptr) {
		character->ContextualWidget->RemoveFromParent();
		character->ContextualWidget = nullptr;
	}
}

// Called every frame
void AShop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

