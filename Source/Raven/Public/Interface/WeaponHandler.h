// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WeaponHandler.generated.h"

class AWeaponBase;
class UWeaponHandlerComponent;

// This class does not need to be modified.
UINTERFACE(MinimalAPI, NotBlueprintable)
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
	UFUNCTION(BlueprintCallable, Category="Weapon Handler Interface")
	virtual UWeaponHandlerComponent* GetWeaponHandlerComponent() const = 0;
};
