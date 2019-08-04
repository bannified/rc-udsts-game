// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerControllerBase.h"
#include "WeaponDataAsset.h"
#include "CharacterBase.generated.h"

class UCameraComponent;
class USpringArmComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBoostEvent, ACharacterBase*, Charater);

UCLASS()
class UDSTS_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

	friend APlayerControllerBase;

public:
	// Sets default values for this character's properties
	ACharacterBase();

	/** Returns controller for this actor. */
	UFUNCTION(BlueprintCallable)
	FORCEINLINE APlayerControllerBase* GetPlayerControllerBase()
	{
		return Cast<APlayerControllerBase>(GetController());
	};

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool HasWeapon(UWeaponDataAsset* weapon)
	{
		return WeaponToLevelMap.Contains(weapon);
	}

	// Returns nullptr if weapon does not exist.
	FORCEINLINE const int* GetWeaponCurrentLevel(const UWeaponDataAsset* weapon)
	{
		return WeaponToLevelMap.Find(weapon);
	}

	FORCEINLINE float GetCurrentMatter() { return CurrentMatter; }

	UFUNCTION(BlueprintCallable)
	void ModifyCurrentMatter(float delta);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "Equipment")
	void UpgradeWeapon(UWeaponDataAsset* weapon);
	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "Equipment")
	void AddLevelsToWeapon(UWeaponDataAsset* weapon, int levels);

	UFUNCTION(NetMulticast, Reliable, WithValidation, BlueprintCallable, Category = "Equipment")
	void SetWeapon(UWeaponDataAsset* weapon);

protected:

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite, Category = "Equipment")
	TMap<UWeaponDataAsset*, int> WeaponToLevelMap;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	UCameraComponent* MainCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera")
	float CameraSensitivity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	float SwimSpeed;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	float CurrentMatter;

	/**
	 * Gameplay components
	 */

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/**
	 * Movement Methods
	 */

	virtual void MoveForward(float value);
	UFUNCTION(BlueprintImplementableEvent, Category = "Movement")
	void ReceiveMoveForward(float value);

	virtual void MoveRight(float value);
	UFUNCTION(BlueprintImplementableEvent, Category = "Movement")
	void ReceiveMoveRight(float value);

	UFUNCTION(Server, Reliable, WithValidation)
	virtual void MoveUp(float value);
	UFUNCTION(BlueprintImplementableEvent, Category = "Movement")
	void ReceiveMoveUp(float value);

	/**
	 * Actions
	 */
	virtual void PrimaryFireStart();
	UFUNCTION(BlueprintImplementableEvent, Category = "Action")
	void ReceivePrimaryFireStart();

	virtual void PrimaryFireEnd();
	UFUNCTION(BlueprintImplementableEvent, Category = "Action")
	void ReceivePrimaryFireEnd();

	virtual void SecondaryFireStart();
	UFUNCTION(BlueprintImplementableEvent, Category = "Action")
	void ReceiveSecondaryFireStart();

	virtual void SecondaryFireEnd();
	UFUNCTION(BlueprintImplementableEvent, Category = "Action")
	void ReceiveSecondaryFireEnd();

	virtual void PreviousEquipment();
	UFUNCTION(BlueprintImplementableEvent, Category = "Action")
	void ReceivePreviousEquipment();
	
	virtual void NextEquipment();
	UFUNCTION(BlueprintImplementableEvent, Category = "Action")
	void ReceiveNextEquipment();

	virtual void MovementModStart();
	UFUNCTION(BlueprintImplementableEvent, Category = "Action")
	void ReceiveMovementModStart();

	virtual void MovementModEnd();
	UFUNCTION(BlueprintImplementableEvent, Category = "Action")
	void ReceiveMovementModEnd();

	/**
	 * General
	 */
	virtual void InteractStart();
	UFUNCTION(BlueprintImplementableEvent, Category = "General")
	void ReceiveInteractStart();

	virtual void InteractEnd();
	UFUNCTION(BlueprintImplementableEvent, Category = "General")
	void ReceiveInteractEnd();

	virtual void Escape();
	UFUNCTION(BlueprintImplementableEvent, Category = "General")
	void ReceiveEscape();

	virtual void Confirm();
	UFUNCTION(BlueprintImplementableEvent, Category = "General")
	void ReceiveConfirm();

	virtual void Pause();
	UFUNCTION(BlueprintImplementableEvent, Category = "General")
	void ReceivePause();

	virtual void Contextual();
	UFUNCTION(BlueprintImplementableEvent, Category = "General")
	void ReceiveContextual();

	/**
	 * Thrusts player in a direction based on current velocity and input direction.
	 */
	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "Advanced Movement")
	void BoostAction();

	UFUNCTION(NetMulticast, Reliable, BlueprintCallable, Category = "Advanced Movement")
	void PlayBoostEffects();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Advanced Movement")
	float Boost_Force;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Advanced Movement")
	float Boost_Cooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Advanced Movement")
	float b_CanBoost;

	FTimerHandle Boost_Cooldown_TimerHandle;

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "Advanced Movement")
	void AddImpulseToCharacterInDirectionWithMagnitude(const FVector directionalVector, const float impulseMagnutide);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float VerticalSwimScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float HorizontalSwimScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float VerticalSwimForce;

	/**
	 * Visual/Sound Effects
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* BoosterSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visuals")
	FVector BoosterParticleScale;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Visuals")
	UParticleSystem* BoosterParticleSystem;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visuals")
	FName BoosterEndSocketName;

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FBoostEvent OnBoostActivated;

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FBoostEvent OnBoostOffCooldown;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visuals")
	FName NozzleEndSocketName;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};