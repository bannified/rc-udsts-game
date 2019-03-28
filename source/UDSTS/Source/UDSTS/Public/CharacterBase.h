// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

class UCameraComponent;
class USpringArmComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBoostEvent, ACharacterBase*, Charater);

UCLASS()
class UDSTS_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();	

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	UCameraComponent* MainCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera")
	float CameraSensitivity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	float SwimSpeed;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/**
	 * Movement Methods
	 */

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void MoveForward(float value);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void MoveRight(float value);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void MoveUp(float value);

	/**
	 * Thrusts player in a direction based on current velocity and input direction.
	 */
	UFUNCTION(BlueprintCallable, Category = "Advanced Movement")
	void Boost_Action();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Advanced Movement")
	float Boost_Force;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Advanced Movement")
	float Boost_Cooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Advanced Movement")
	float b_CanBoost;

	FTimerHandle Boost_Cooldown_TimerHandle;

	UFUNCTION(BlueprintCallable, Category = "Advanced Movement")
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

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
