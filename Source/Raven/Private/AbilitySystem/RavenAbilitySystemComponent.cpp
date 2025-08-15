// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/RavenAbilitySystemComponent.h"

#include "AbilitySystem/GameplayAbility/RavenGameplayAbility.h"

void URavenAbilitySystemComponent::AbilitySpecInputPressed(FGameplayAbilitySpec& Spec)
{
	Super::AbilitySpecInputPressed(Spec);

	if (Spec.IsActive())
	{
		InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputPressed, Spec.Handle,
			Spec.Ability->GetCurrentActivationInfo().GetActivationPredictionKey());
	}
}

void URavenAbilitySystemComponent::AbilitySpecInputReleased(FGameplayAbilitySpec& Spec)
{
	Super::AbilitySpecInputReleased(Spec);

	if (Spec.IsActive())
	{
		InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputReleased, Spec.Handle,
			Spec.Ability->GetCurrentActivationInfo().GetActivationPredictionKey());
	}
}

void URavenAbilitySystemComponent::HoldInputForAbilityByTag(const FGameplayTag& InputTag)
{
	TArray<FGameplayAbilitySpec>& ActivableAbilities = GetActivatableAbilities();

	for (FGameplayAbilitySpec& AbilitySpec : ActivableAbilities)
	{
		if (AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec);
			TryActivateAbility(AbilitySpec.Handle);

			return;
		}
	}
}

void URavenAbilitySystemComponent::ReleaseInputForAbilityByTag(const FGameplayTag& InputTag)
{
	TArray<FGameplayAbilitySpec>& ActivableAbilities = GetActivatableAbilities();

	for (FGameplayAbilitySpec& AbilitySpec : ActivableAbilities)
	{
		if (AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
		{
			AbilitySpecInputReleased(AbilitySpec);

			return;
		}
	}
}

void URavenAbilitySystemComponent::GrantAbilities(const TArray<TSubclassOf<UGameplayAbility>>& GameplayAbilities)
{
	for (TSubclassOf<UGameplayAbility> AbilityClass : GameplayAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec{AbilityClass, 1};

		if (const URavenGameplayAbility* RavenGameplayAbility = Cast<URavenGameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.GetDynamicSpecSourceTags().AddTag(RavenGameplayAbility->GetInputTag());
			GiveAbility(AbilitySpec);
		}
	}
}
