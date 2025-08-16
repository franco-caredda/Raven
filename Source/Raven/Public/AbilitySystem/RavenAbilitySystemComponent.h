// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "RavenAbilitySystemComponent.generated.h"

struct FGameplayTag;

enum class EAbilityInputID : uint8;

/**
 * 
 */
UCLASS()
class RAVEN_API URavenAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	void HoldInputForAbilityByID(EAbilityInputID InputID);
	void ReleaseInputForAbilityByID(EAbilityInputID InputID);

	void GrantAbilities(const TArray<TSubclassOf<UGameplayAbility>>& GameplayAbilities);
};
