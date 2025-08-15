// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RavenCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/RavenAbilitySystemComponent.h"

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

	if (URavenAbilitySystemComponent* RavenAbilitySystemComponent =
		Cast<URavenAbilitySystemComponent>(AbilitySystemComponent))
	{
		RavenAbilitySystemComponent->GrantAbilities(DefaultGameplayAbilities);
	}
}

