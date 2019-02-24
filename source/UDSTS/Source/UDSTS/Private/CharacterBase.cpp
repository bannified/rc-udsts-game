// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

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
	resultVector.Y *= VerticalSwimScale;
	resultVector.X *= HorizontalSwimScale;

	AddMovementInput(resultVector, value);
}

void ACharacterBase::MoveRight(float value)
{
	FRotator rot = FRotator(0, 0, 0);

	UKismetMathLibrary::BreakRotator(GetControlRotation(), rot.Roll, rot.Pitch, rot.Yaw);
	rot.Roll = 0;

	FVector resultVector = UKismetMathLibrary::GetForwardVector(rot);

	resultVector.Y *= VerticalSwimScale;
	resultVector.X *= HorizontalSwimScale;

	AddMovementInput(UKismetMathLibrary::GetRightVector(rot), value);
}

void ACharacterBase::MoveUp(float value)
{
	Super::AddMovementInput(FVector(0.0, 0.0, VerticalSwimScale), value);
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACharacterBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACharacterBase::MoveRight);
	PlayerInputComponent->BindAxis("Ascend", this, &ACharacterBase::MoveUp);

	PlayerInputComponent->BindAxis("LookUp", this, &ACharacterBase::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookRight", this, &ACharacterBase::AddControllerYawInput);


}

