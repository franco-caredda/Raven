 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/RavenCharacterBase.h"
#include "RavenCharacterPlayable.generated.h"

class USpringArmComponent;
class UCameraComponent;

/**
 * Characters of this class should only be possessed by Player Controller
 */
UCLASS()
class RAVEN_API ARavenCharacterPlayable : public ARavenCharacterBase
{
	GENERATED_BODY()
public:
	ARavenCharacterPlayable();

	virtual void PossessedBy(AController* NewController) override;
	virtual void Tick(float DeltaTime) override;
protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCameraComponent> CameraComponent;
};
