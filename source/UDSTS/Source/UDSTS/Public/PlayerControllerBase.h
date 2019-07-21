// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerBase.generated.h"

class ACharacterBase;

/**
 * 
 */
UCLASS()
class UDSTS_API APlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

	virtual void SetupInputComponent() override;

protected:
	/* Axis-based Input */
	virtual void MoveForward(float value);
	virtual void MoveRight(float value);
	virtual void MoveUp(float value);

	virtual void LookUp(float value);
	virtual void LookRight(float value);

	/* Action Inputs */

		/* Gameplay */
	virtual void PrimaryFireStart();
	virtual void PrimaryFireEnd();
	virtual void SecondaryFireStart();
	virtual void SecondaryFireEnd();

	virtual void MovementModStart();
	virtual void MovementModEnd();
	virtual void InteractStart();
	virtual void InteractEnd();

	virtual void PreviousEquipment();
	virtual void NextEquipment();

		/* General */
	virtual void Escape();
	virtual void Contextual();
	virtual void Confirm();
	virtual void Pause();

	virtual void Possess(APawn* aPawn) override;
	
private:
	ACharacterBase* m_Character;
};
