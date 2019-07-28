// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerControllerBase.h"
#include "CharacterBase.h"
#include "UDSTS.h"

APlayerControllerBase::APlayerControllerBase()
{
	m_IsInputToCharacterActive = true;

}

void APlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();

}

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

	InputComponent->BindAction("Shop_Buy", EInputEvent::IE_Pressed, this, &APlayerControllerBase::ShopBuy);
	InputComponent->BindAction("_UILeft", EInputEvent::IE_Pressed, this, &APlayerControllerBase::UILeft);
	InputComponent->BindAction("_UIRight", EInputEvent::IE_Pressed, this, &APlayerControllerBase::UIRight);
	InputComponent->BindAction("_UIUp", EInputEvent::IE_Pressed, this, &APlayerControllerBase::UIUp);
	InputComponent->BindAction("_UIDown", EInputEvent::IE_Pressed, this, &APlayerControllerBase::UIDown);
}

void APlayerControllerBase::MoveForward(float value)
{
	if (m_Character)
	{
		m_Character->MoveForward(value);
	}
}

void APlayerControllerBase::MoveRight(float value)
{
	if (m_IsInputToCharacterActive && m_Character)
	{
		m_Character->MoveRight(value);
	}
}

void APlayerControllerBase::MoveUp(float value)
{
	if (m_IsInputToCharacterActive && m_Character)
	{
		m_Character->MoveUp(value);
	}
}

void APlayerControllerBase::LookUp(float value)
{
	if (m_IsInputToCharacterActive && m_Character)
	{
		m_Character->AddControllerPitchInput(value);
	}
}

void APlayerControllerBase::LookRight(float value)
{
	if (m_IsInputToCharacterActive && m_Character)
	{
		m_Character->AddControllerYawInput(value);
	}
}

void APlayerControllerBase::PrimaryFireStart()
{
	if (m_IsInputToCharacterActive && m_Character)
	{
		m_Character->PrimaryFireStart();
		UE_LOG(LogTemp, Log, TEXT("PrimaryFireStart"));
	}
}

void APlayerControllerBase::PrimaryFireEnd()
{
	if (m_IsInputToCharacterActive && m_Character)
	{
		m_Character->PrimaryFireEnd();
		UE_LOG(LogTemp, Log, TEXT("PrimaryFireEnd"));

	}
}

void APlayerControllerBase::SecondaryFireStart()
{
	if (m_IsInputToCharacterActive && m_Character)
	{
		m_Character->SecondaryFireStart();
	}
}

void APlayerControllerBase::SecondaryFireEnd()
{
	if (m_IsInputToCharacterActive && m_Character)
	{
		m_Character->SecondaryFireEnd();
	}
}

void APlayerControllerBase::MovementModStart()
{
	if (m_IsInputToCharacterActive && m_Character)
	{
		m_Character->MovementModStart();
		UE_LOG(LogTemp, Log, TEXT("MovementModStart"));

	}
}

void APlayerControllerBase::MovementModEnd()
{
	if (m_IsInputToCharacterActive && m_Character)
	{
		m_Character->MovementModEnd();
	}
}

void APlayerControllerBase::InteractStart()
{
	if (m_IsInputToCharacterActive && m_Character)
	{
		m_Character->InteractStart();
	}
}

void APlayerControllerBase::InteractEnd()
{
	if (m_IsInputToCharacterActive && m_Character)
	{
		m_Character->InteractEnd();
	}
}

void APlayerControllerBase::PreviousEquipment()
{
	if (m_IsInputToCharacterActive && m_Character)
	{
		m_Character->PreviousEquipment();
	}
}

void APlayerControllerBase::NextEquipment()
{
	if (m_IsInputToCharacterActive && m_Character)
	{
		m_Character->NextEquipment();
	}
}

void APlayerControllerBase::Escape()
{
	if (m_IsInputToCharacterActive && m_Character)
	{
		m_Character->Escape();
	}
}

void APlayerControllerBase::Contextual()
{
	if (m_IsInputToCharacterActive && m_Character)
	{
		m_Character->Contextual();
	}
}

void APlayerControllerBase::Confirm()
{
	if (m_IsInputToCharacterActive && m_Character)
	{
		m_Character->Confirm();
	}
}

void APlayerControllerBase::Pause()
{
	if (m_IsInputToCharacterActive && m_Character)
	{
		m_Character->Pause();
	}
}

void APlayerControllerBase::ShopBuy()
{
	OnShopBuy.Broadcast(this);
}

void APlayerControllerBase::UILeft()
{
	OnUILeft.Broadcast(this);
}

void APlayerControllerBase::UIRight()
{
	OnUIRight.Broadcast(this);
}

void APlayerControllerBase::UIUp()
{
	OnUIUp.Broadcast(this);
}

void APlayerControllerBase::UIDown()
{
	OnUIDown.Broadcast(this);
}

void APlayerControllerBase::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	PRINT_INFO("Possessed called in ACharacterBase in PC: %s", *(this->GetName()));

	ACharacterBase* character = Cast<ACharacterBase>(GetPawn());
	if (character != nullptr)
	{
		m_Character = character;
	}
	else
	{
		PRINT_INFO("Possessing with no ACharacterBase in PC: %s", *(this->GetName()));
	}
}

void APlayerControllerBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlayerControllerBase, m_Character);

}
