// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
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
	virtual void AbilitySpecInputPressed(FGameplayAbilitySpec& Spec) override;
	virtual void AbilitySpecInputReleased(FGameplayAbilitySpec& Spec) override;
	
	/**
	 * Implements lazy activation of the ability with InputTag and sets its state to Pressed
	 * @param InputTag Unique Input Tag
	 */
	void HoldInputForAbilityByTag(const FGameplayTag& InputTag);

	/**
	 * Implements lazy Release of the ability with InputTag
	 * @param InputTag Unique Input Tag
	 */
	void ReleaseInputForAbilityByTag(const FGameplayTag& InputTag);

	void GrantAbilities(const TArray<TSubclassOf<UGameplayAbility>>& GameplayAbilities);
};
