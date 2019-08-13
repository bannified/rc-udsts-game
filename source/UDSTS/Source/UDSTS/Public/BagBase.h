// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BagBase.generated.h"

class USoundCue;
class USceneComponent;
class UStaticMeshComponent;
class UAudioComponent;

UCLASS()
class UDSTS_API ABagBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABagBase();

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	bool IsMatterSufficient(float value);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "Gameplay")
	void ModifyMatterBy(float deltaMatter, bool overflow = false);

	UFUNCTION(NetMulticast, Unreliable, BlueprintCallable, Category = "Gameplay")
	void PlayBoostSound();

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UStaticMeshComponent* GetMesh()
	{
		return BagMeshComponent;
	};

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* BagMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UAudioComponent* AudioComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UStaticMesh> BagMeshClassOverride;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadWrite)
	float Matter;

	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadWrite)
	float MaxMatter;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<USoundCue> SoundCueClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
