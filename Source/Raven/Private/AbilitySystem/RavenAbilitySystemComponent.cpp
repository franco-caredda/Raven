// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/RavenAbilitySystemComponent.h"

#include "AbilitySystem/GameplayAbility/RavenGameplayAbility.h"

bool URavenAbilitySystemComponent::AbilityInputPressed(const FGameplayTag& InputTag)
{
	for (FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		if (Spec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(Spec);
			bool bSuccess = TryActivateAbility(Spec.Handle);

			return bSuccess;
		}
	}

	return false;
}

bool URavenAbilitySystemComponent::AbilityInputReleased(const FGameplayTag& InputTag)
{
	for (FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		if (Spec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
		{
			AbilitySpecInputReleased(Spec);

			return true;
		}
	}

	return false;
}

FGameplayAbilitySpecHandle URavenAbilitySystemComponent::GrantAbility(const TSubclassOf<UGameplayAbility>& GameplayAbilityClass)
{
	FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec{GameplayAbilityClass, 1};

	if (const URavenGameplayAbility* RavenGameplayAbility = Cast<URavenGameplayAbility>(AbilitySpec.Ability))
	{
		AbilitySpec.GetDynamicSpecSourceTags()
				   .AddTag(RavenGameplayAbility->GetInputTag());
	}	

	return GiveAbility(AbilitySpec);
}

void URavenAbilitySystemComponent::GrantAbilities(const TArray<TSubclassOf<UGameplayAbility>>& GameplayAbilities)
{
	for (TSubclassOf<UGameplayAbility> AbilityClass : GameplayAbilities)
	{
		GrantAbility(AbilityClass);
	}
}
