// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RavenCharacterBase.h"

#include "AbilitySystemComponent.h"

ARavenCharacterBase::ARavenCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

UAbilitySystemComponent* ARavenCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ARavenCharacterBase::GrantDefaultAbilities()
{
	if (!AbilitySystemComponent)
	{
		return;
	}

	for (TSubclassOf<UGameplayAbility> AbilityClass : DefaultGameplayAbilities)
	{
		FGameplayAbilitySpec AbilitySpec =
			AbilitySystemComponent->BuildAbilitySpecFromClass(AbilityClass, 1,
				0);
		GrantedAbilities.Add(AbilitySystemComponent->GiveAbility(AbilitySpec));
	}
}

