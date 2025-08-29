// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/RavenAbilitySystemComponent.h"

#include "AbilitySystem/GameplayAbility/RavenGameplayAbility.h"

bool URavenAbilitySystemComponent::TryActivateAbilityByID(EAbilityInputID InputID)
{
	for (const FGameplayAbilitySpec& CurrentAbilitySpec : GetActivatableAbilities())
	{
		UE_LOG(LogTemp, Display, TEXT("Ability Input Id [%d] Status [%d]"),
			CurrentAbilitySpec.InputID, CurrentAbilitySpec.IsActive());
		
		if (CurrentAbilitySpec.InputID == static_cast<int32>(InputID))
		{
			return TryActivateAbility(CurrentAbilitySpec.Handle);
		}
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
	TryActivateAbilityByID(InputID);
}

void URavenAbilitySystemComponent::ReleaseInputForAbilityByID(EAbilityInputID InputID)
{
	if (InputID == EAbilityInputID::None || InputID == EAbilityInputID::MAX)
	{
		return;
	}
	
	AbilityLocalInputReleased(static_cast<uint8>(InputID));
}

FGameplayAbilitySpecHandle URavenAbilitySystemComponent::GrantAbility(const TSubclassOf<UGameplayAbility>& GameplayAbilityClass)
{
	FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec{GameplayAbilityClass, 1};

	if (const URavenGameplayAbility* RavenGameplayAbility = Cast<URavenGameplayAbility>(AbilitySpec.Ability))
	{
		AbilitySpec.InputID = static_cast<int32>(RavenGameplayAbility->GetInputID());
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
