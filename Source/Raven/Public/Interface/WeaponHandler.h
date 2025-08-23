// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WeaponHandler.generated.h"

class AWeaponBase;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UWeaponHandler : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RAVEN_API IWeaponHandler
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, Category="Weapon Handler")
	void AttachWeapon(AWeaponBase* Weapon);
	virtual void AttachWeapon_Implementation(AWeaponBase* Weapon) = 0;

	UFUNCTION(BlueprintNativeEvent, Category="Weapon Handler")
	void DetachWeapon();
	virtual void DetachWeapon_Implementation() = 0;
};
