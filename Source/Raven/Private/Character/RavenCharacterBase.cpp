// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RavenCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/RavenAbilitySystemComponent.h"

#include "DataAsset/RavenGameplayAbilityDataAsset.h"

#include "RavenGameplayTagRegistry.h"

ARavenCharacterBase::ARavenCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

UAbilitySystemComponent* ARavenCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ARavenCharacterBase::LightAttack() const
{
	FRavenGameplayTagRegistry& TagRegistry = FRavenGameplayTagRegistry::Get();
	ActivateAbility(GrantedAbilities[TagRegistry.GetRavenInputAttackLight()]);
}

void ARavenCharacterBase::HeavyAttack() const
{
	FRavenGameplayTagRegistry& TagRegistry = FRavenGameplayTagRegistry::Get();
	ActivateAbility(GrantedAbilities[TagRegistry.GetRavenInputAttackHeavy()]);
}

void ARavenCharacterBase::Block() const
{
}

void ARavenCharacterBase::Parry() const
{
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
		const TArray<FRavenGameplayAbilityData>& GameplayAbilityDataSet =
			GameplayAbilityDataAsset->GetGameplayAbilityDataSet();

		for (const auto& GameplayAbilityData : GameplayAbilityDataSet)
		{
			GrantedAbilities.Add(GameplayAbilityData.InputTag,
				RavenAbilitySystemComponent->GrantAbility(GameplayAbilityData.GameplayAbility));
		}
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

void ARavenCharacterBase::ActivateAbility(FGameplayAbilitySpecHandle AbilitySpecHandle) const
{
	if (AbilitySpecHandle.IsValid())
	{
		AbilitySystemComponent->TryActivateAbility(AbilitySpecHandle);
	}
}

void ARavenCharacterBase::InitEffects()
{
	ApplyEffect(DefaultPrimaryAttributesClass);
	ApplyEffect(DefaultSecondaryAttributesClass);
	ApplyEffect(DefaultVitalAttributesClass);

	ApplyDefaultEffects();
}

