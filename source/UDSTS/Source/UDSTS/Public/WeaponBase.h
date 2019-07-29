// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

class USoundCue;
class USceneComponent;
class UStaticMeshComponent;
class UAudioComponent;
class ANozzleBase;
class ACharacterBase;
class UWeaponDataAsset;

UCLASS()
class UDSTS_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "Combat")
	void PrimaryStart();
	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "Combat")
	void PrimaryUpdate();
	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "Combat")
	void PrimaryEnd();

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "Combat")
	void SecondaryStart();
	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "Combat")
	void SecondaryUpdate();
	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "Combat")
	void SecondaryEnd();

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "Mods")
	void SetNozzleProperties(UWeaponDataAsset* nozzleData, int level);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "Mods")
	void InitNozzle(ANozzleBase* Nozzle, UWeaponDataAsset* nozzleData);

	UFUNCTION(BlueprintCallable, Category = "Utility")
	float ConvertRawMatterToFinalMatter(float inMatter);

	UFUNCTION(NetMulticast, Unreliable, BlueprintCallable, Category = "Audio")
	void PlayPrimarySound();
	UFUNCTION(NetMulticast, Unreliable, BlueprintCallable, Category = "Audio")
	void PlaySecondarySound();
	UFUNCTION(NetMulticast, Unreliable, BlueprintCallable, Category = "Audio")
	void StopPrimarySound();

protected:

	/* Components */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* WeaponMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UAudioComponent* AudioComponent;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* Settings */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UStaticMesh> WeaponMeshClassOverride;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite)
	ACharacterBase* Character;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite)
	ANozzleBase* CurrentNozzle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<USoundCue> BlowSoundCueClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<USoundCue> SuckSoundCueClass;

	/* Runtime variables */
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	float PrimaryBaseCooldown;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	float SecondaryBaseCooldown;
	
	/* Virtual getters */
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	virtual float GetPrimaryCooldown();
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	virtual float GetSecondaryCooldown();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
