// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UnrealNetwork.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));

	SpringArmComponent->SetupAttachment(RootComponent);

	SpringArmComponent->bUsePawnControlRotation = true;

	MainCamera->SetupAttachment(SpringArmComponent);

	MainCamera->SetRelativeLocation(FVector(0.0, 50.0, 80.0));

	SwimSpeed = 300.0f;

	HorizontalSwimScale = 1.0f;
	VerticalSwimScale = 1.0f;

	VerticalSwimForce = 300.0f;

	BoosterEndSocketName = "booster_end";

	NozzleEndSocketName = "nozzle_end";

	Boost_Force = 1000.0f;
	Boost_Cooldown = 10.0f;
	b_CanBoost = true;

	CurrentMatter = 100.0f;

	WeaponToLevelMap = {};
}

void ACharacterBase::ModifyCurrentMatter(float delta)
{
	CurrentMatter += delta;
}

void ACharacterBase::AddLevelsToWeapon_Implementation(UWeaponDataAsset* weapon, int levels)
{
	if (!WeaponToLevelMap.Contains(weapon)) {
		WeaponToLevelMap.FindOrAdd(weapon);
		WeaponToLevelMap[weapon] += levels - 1;
	}
	else {
		WeaponToLevelMap[weapon] += levels;
	}
}

bool ACharacterBase::AddLevelsToWeapon_Validate(UWeaponDataAsset* weapon, int levels)
{
	return true;
}

void ACharacterBase::UpgradeWeapon_Implementation(UWeaponDataAsset* weapon)
{
	AddLevelsToWeapon(weapon, 1);
}

bool ACharacterBase::UpgradeWeapon_Validate(UWeaponDataAsset* weapon)
{
	return weapon->IsBuyableByCharacter(this);
}


void ACharacterBase::SetWeapon_Implementation(UWeaponDataAsset* weapon)
{

}

bool ACharacterBase::SetWeapon_Validate(UWeaponDataAsset* weapon)
{
	return true;
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	GetCharacterMovement()->MaxSwimSpeed = SwimSpeed;
}

void ACharacterBase::MoveForward(float value)
{
	FRotator rot = FRotator(0, 0, 0);

	UKismetMathLibrary::BreakRotator(GetControlRotation(), rot.Roll, rot.Pitch, rot.Yaw);
	rot.Roll = 0;

	FVector resultVector = UKismetMathLibrary::GetForwardVector(rot);
	resultVector.Z *= VerticalSwimScale;
	resultVector.X *= HorizontalSwimScale;

	AddMovementInput(resultVector, value);

	ReceiveMoveForward(value);
}

void ACharacterBase::MoveRight(float value)
{
	FRotator rot = FRotator(0, 0, 0);

	UKismetMathLibrary::BreakRotator(GetControlRotation(), rot.Roll, rot.Pitch, rot.Yaw);
	rot.Roll = 0;

	FVector resultVector = UKismetMathLibrary::GetRightVector(rot);

	resultVector.Z *= VerticalSwimScale;
	resultVector.X *= HorizontalSwimScale;

	AddMovementInput(resultVector, value);

	ReceiveMoveRight(value);
}

void ACharacterBase::MoveUp_Implementation(float value)
{
	GetCharacterMovement()->AddForce(FVector(0.0, 0.0, value * VerticalSwimForce));
	ReceiveMoveUp(value);
}

bool ACharacterBase::MoveUp_Validate(float value)
{
	return true;
}

void ACharacterBase::PrimaryFireStart()
{
	ReceivePrimaryFireStart();
}

void ACharacterBase::PrimaryFireEnd()
{
	ReceivePrimaryFireEnd();

}

void ACharacterBase::SecondaryFireStart()
{
	ReceiveSecondaryFireStart();
}

void ACharacterBase::SecondaryFireEnd()
{
	ReceiveSecondaryFireEnd();
}

void ACharacterBase::PreviousEquipment()
{
	ReceivePreviousEquipment();
}

void ACharacterBase::NextEquipment()
{
	ReceiveNextEquipment();
}

void ACharacterBase::MovementModStart()
{
	BoostAction();

	ReceiveMovementModStart();
}

void ACharacterBase::MovementModEnd()
{
	ReceiveMovementModEnd();
}

void ACharacterBase::InteractStart()
{
	ReceiveInteractStart();
}

void ACharacterBase::InteractEnd()
{
	ReceiveInteractEnd();
}

void ACharacterBase::Escape()
{
	ReceiveEscape();
}

void ACharacterBase::Confirm()
{
	ReceiveConfirm();
}

void ACharacterBase::Pause()
{
	ReceivePause();
}

void ACharacterBase::Contextual()
{
	ReceiveContextual();
}

void ACharacterBase::PlayBoostEffects_Implementation()
{
	if (BoosterParticleSystem != nullptr) {
		UGameplayStatics::SpawnEmitterAttached(BoosterParticleSystem, GetMesh(), BoosterEndSocketName, FVector::ZeroVector, FRotator::ZeroRotator, BoosterParticleScale, EAttachLocation::KeepRelativeOffset, true, EPSCPoolMethod::AutoRelease);
	}

	if (BoosterSound != nullptr) {
		UGameplayStatics::SpawnSoundAttached(BoosterSound, GetMesh(), BoosterEndSocketName, FVector::ZeroVector, EAttachLocation::KeepRelativeOffset, false, 0.5f);
	}
}

void ACharacterBase::BoostAction_Implementation()
{
	if (!b_CanBoost) {
		return;
	}

	FVector inputVector = GetInputAxisValue(FName("MoveForward")) * GetActorForwardVector()
		+ GetInputAxisValue(FName("MoveRight")) * GetActorRightVector();
	inputVector.Normalize();

	FVector characterVelocity = GetCharacterMovement()->Velocity;
	characterVelocity.Normalize();

	FVector resultDirectionVector = (FMath::IsNearlyZero(inputVector.Size()) && FMath::IsNearlyZero(characterVelocity.Size())) ? GetActorForwardVector() : characterVelocity + inputVector;
	resultDirectionVector.Normalize();

	AddImpulseToCharacterInDirectionWithMagnitude(resultDirectionVector, Boost_Force);

	this->b_CanBoost = false;

	OnBoostActivated.Broadcast(this);

	PlayBoostEffects();

	GetWorldTimerManager().SetTimer(Boost_Cooldown_TimerHandle, [&]()
	{
		this->b_CanBoost = true;
		OnBoostOffCooldown.Broadcast(this);
	}, Boost_Cooldown, false);
}

bool ACharacterBase::BoostAction_Validate()
{
	return true;
}

void ACharacterBase::AddImpulseToCharacterInDirectionWithMagnitude_Implementation(const FVector directionalVector, const float impulseMagnutide)
{
	GetCharacterMovement()->AddImpulse(directionalVector * impulseMagnutide, true);
}

bool ACharacterBase::AddImpulseToCharacterInDirectionWithMagnitude_Validate(const FVector directionalVector, const float impulseMagnutide)
{
	return true;
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACharacterBase, b_CanBoost);
	DOREPLIFETIME(ACharacterBase, WeaponToLevelMap);

	DOREPLIFETIME(ACharacterBase, CurrentMatter);
}