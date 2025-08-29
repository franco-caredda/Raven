// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, NotBlueprintable)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *	This interface is a helper for calling abilities on actors.
 *	It can be used by BTTasks, Anim Notifies, etc.
 */
class RAVEN_API ICombatInterface
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category="Combat Interface")
	virtual void LightAttack() const = 0;

	UFUNCTION(BlueprintCallable, Category="Combat Interface")
	virtual void HeavyAttack() const = 0;

	UFUNCTION(BlueprintCallable, Category="Combat Interface")
	virtual void Block() const = 0;

	UFUNCTION(BlueprintCallable, Category="Combat Interface")
	virtual void Parry() const = 0;
};
