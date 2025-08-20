// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/RavenAbilitySystemComponent.h"

#include "AbilitySystem/GameplayAbility/RavenGameplayAbility.h"

bool URavenAbilitySystemComponent::TryActivateAbilityByID(EAbilityInputID InputID)
{
	TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;
	GetAllAbilities(AbilitySpecHandles);

	FGameplayAbilitySpecHandle* AbilitySpecHandle = nullptr;
	for (FGameplayAbilitySpecHandle CurrentAbilitySpecHandle : AbilitySpecHandles)
	{
		FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromHandle(CurrentAbilitySpecHandle);
		if (AbilitySpec && AbilitySpec->InputID == static_cast<int32>(InputID))
		{
			AbilitySpecHandle = &CurrentAbilitySpecHandle;	
			break;
		}
	}

	if (AbilitySpecHandle)
	{
		return TryActivateAbility(*AbilitySpecHandle);
	}

	return false;
}

void URavenAbilitySystemComponent::HoldInputForAbilityByID(EAbilityInputID InputID)
{
	if (InputID == EAbilityInputID::None || InputID == EAbilityInputID::MAX)
	{
		return;
	}

	// This function might not notify the server that an ability was activated.
	// Providing an RPC might be needed.
	AbilityLocalInputPressed(static_cast<uint8>(InputID));
}

void URavenAbilitySystemComponent::ReleaseInputForAbilityByID(EAbilityInputID InputID)
{
	if (InputID == EAbilityInputID::None || InputID == EAbilityInputID::MAX)
	{
		return;
	}
	
	AbilityLocalInputReleased(static_cast<uint8>(InputID));
}

void URavenAbilitySystemComponent::GrantAbilities(const TArray<TSubclassOf<UGameplayAbility>>& GameplayAbilities)
{
	for (TSubclassOf<UGameplayAbility> AbilityClass : GameplayAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec{AbilityClass, 1};

		if (const URavenGameplayAbility* RavenGameplayAbility = Cast<URavenGameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.InputID = static_cast<int32>(RavenGameplayAbility->GetInputID());
			GiveAbility(AbilitySpec);
		}
	}
}
