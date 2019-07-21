// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerControllerBase.h"
#include "CharacterBase.h"

void APlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &APlayerControllerBase::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &APlayerControllerBase::MoveRight);
	InputComponent->BindAxis("MoveUp", this, &APlayerControllerBase::MoveUp);

	InputComponent->BindAxis("LookUp", this, &APlayerControllerBase::LookUp);
	InputComponent->BindAxis("LookRight", this, &APlayerControllerBase::LookRight);

	InputComponent->BindAction("PrimaryFire", EInputEvent::IE_Pressed, this, &APlayerControllerBase::PrimaryFireStart);
	InputComponent->BindAction("PrimaryFire", EInputEvent::IE_Released, this, &APlayerControllerBase::PrimaryFireEnd);

	InputComponent->BindAction("SecondaryFire", EInputEvent::IE_Pressed, this, &APlayerControllerBase::SecondaryFireStart);
	InputComponent->BindAction("SecondaryFire", EInputEvent::IE_Released, this, &APlayerControllerBase::SecondaryFireEnd);

	InputComponent->BindAction("Interact", EInputEvent::IE_Pressed, this, &APlayerControllerBase::InteractStart);
	InputComponent->BindAction("Interact", EInputEvent::IE_Released, this, &APlayerControllerBase::InteractEnd);

	InputComponent->BindAction("PreviousEquipment", EInputEvent::IE_Pressed, this, &APlayerControllerBase::PreviousEquipment);
	InputComponent->BindAction("NextEquipment", EInputEvent::IE_Pressed, this, &APlayerControllerBase::NextEquipment);

	InputComponent->BindAction("MovementMod", EInputEvent::IE_Pressed, this, &APlayerControllerBase::MovementModStart);
	InputComponent->BindAction("MovementMod", EInputEvent::IE_Released, this, &APlayerControllerBase::MovementModEnd);

	InputComponent->BindAction("Escape", EInputEvent::IE_Pressed, this, &APlayerControllerBase::Escape);
	InputComponent->BindAction("Confirm", EInputEvent::IE_Pressed, this, &APlayerControllerBase::Confirm);
	InputComponent->BindAction("Pause", EInputEvent::IE_Pressed, this, &APlayerControllerBase::Pause);
	InputComponent->BindAction("Contextual", EInputEvent::IE_Pressed, this, &APlayerControllerBase::Contextual);
}

void APlayerControllerBase::MoveForward(float value)
{
	m_Character->MoveForward(value);
}

void APlayerControllerBase::MoveRight(float value)
{
	m_Character->MoveRight(value);
}

void APlayerControllerBase::MoveUp(float value)
{
	m_Character->MoveUp(value);
}

void APlayerControllerBase::LookUp(float value)
{
	m_Character->AddControllerPitchInput(value);
}

void APlayerControllerBase::LookRight(float value)
{
	m_Character->AddControllerYawInput(value);
}

void APlayerControllerBase::PrimaryFireStart()
{
	m_Character->PrimaryFireStart();
}

void APlayerControllerBase::PrimaryFireEnd()
{
	m_Character->PrimaryFireEnd();
}

void APlayerControllerBase::SecondaryFireStart()
{
	m_Character->SecondaryFireStart();
}

void APlayerControllerBase::SecondaryFireEnd()
{
	m_Character->SecondaryFireEnd();
}

void APlayerControllerBase::MovementModStart()
{
	m_Character->MovementModStart();
}

void APlayerControllerBase::MovementModEnd()
{
	m_Character->MovementModEnd();
}

void APlayerControllerBase::InteractStart()
{
	m_Character->InteractStart();
}

void APlayerControllerBase::InteractEnd()
{
	m_Character->InteractEnd();
}

void APlayerControllerBase::PreviousEquipment()
{
	m_Character->PreviousEquipment();
}

void APlayerControllerBase::NextEquipment()
{
	m_Character->NextEquipment();
}

void APlayerControllerBase::Escape()
{
	m_Character->Escape();
}

void APlayerControllerBase::Contextual()
{

}

void APlayerControllerBase::Confirm()
{

}

void APlayerControllerBase::Pause()
{

}

void APlayerControllerBase::Possess(APawn* aPawn)
{
	Super::Possess(aPawn);

	ACharacterBase* character = Cast<ACharacterBase>(GetPawn());
	if (character != nullptr) {
		m_Character = character;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerControllerBase isn't possessing "));
	}
}
