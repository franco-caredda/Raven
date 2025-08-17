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

void ARavenCharacterBase::ApplyEffect(TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
		
	FGameplayEffectSpecHandle EffectSpecHandle =
		AbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass, 1, ContextHandle);
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data);
}

void ARavenCharacterBase::ApplyDefaultEffects()
{
	if (!AbilitySystemComponent)
	{
		return;
	}

	for (TSubclassOf<UGameplayEffect> GameplayEffectClass : DefaultGameplayEffects)
	{
		ApplyEffect(GameplayEffectClass);
	}
}

void ARavenCharacterBase::InitEffects()
{
	ApplyEffect(DefaultPrimaryAttributesClass);
	ApplyEffect(DefaultSecondaryAttributesClass);
	ApplyEffect(DefaultVitalAttributesClass);

	ApplyDefaultEffects();
}

