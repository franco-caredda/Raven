// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "RavenGameplayAbilityTypes.h"
#include "RavenGameplayAbility.generated.h"

struct FGameplayTag;

/**
 * 
 */
UCLASS()
class RAVEN_API URavenGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	FORCEINLINE EAbilityInputID GetInputID() const { return InputID; }
protected:
	UPROPERTY(EditDefaultsOnly, Category="Input")
	EAbilityInputID InputID;
};
