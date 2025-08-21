// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbility/RavenGameplayAbility.h"
#include "RavenAbilitySystemComponent.generated.h"

struct FGameplayTag;

/**
 * 
 */
UCLASS()
class RAVEN_API URavenAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	bool TryActivateAbilityByID(EAbilityInputID InputID);
	
	void HoldInputForAbilityByID(EAbilityInputID InputID);
	void ReleaseInputForAbilityByID(EAbilityInputID InputID);

	void GrantAbilities(const TArray<TSubclassOf<UGameplayAbility>>& GameplayAbilities);
};
