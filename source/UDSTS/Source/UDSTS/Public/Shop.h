// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shop.generated.h"

class UUserWidget;
class ABase;
class UBoxComponent;
class ACharacterBase;

UCLASS()
class UDSTS_API AShop : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShop();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Visual")
	USceneComponent* RootSceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gameplay")
	UBoxComponent* EntryBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gameplay")
	UBoxComponent* ExitBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> InteractWidgetClass;
	UPROPERTY(BlueprintReadOnly)
	UUserWidget* InteractWidgetInstance;

	UPROPERTY(BlueprintReadOnly)
	ACharacterBase* CurrentCharacter;

	UFUNCTION(BlueprintCallable)
	void ShowInteractWidget(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION(BlueprintCallable)
	void HideInteractWidget(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
