// Fill out your copyright notice in the Description page of Project Settings.


#include "RavenGameplayTagRegistry.h"
#include "GameplayTagsManager.h"

FRavenGameplayTagRegistry FRavenGameplayTagRegistry::GameplayTagRegistry;

FRavenGameplayTagRegistry::FRavenGameplayTagRegistry()
{
}

FRavenGameplayTagRegistry& FRavenGameplayTagRegistry::Get() noexcept
{
	return GameplayTagRegistry;
}

void FRavenGameplayTagRegistry::InitRegistry()
{
	UGameplayTagsManager& GameplayTagsManager = UGameplayTagsManager::Get();

	RavenAbilityAttackLight = GameplayTagsManager.AddNativeGameplayTag(FName("Raven.Ability.Attack.Light"),
		FString("Tells the ability system that this ability is a light attack"));
	RavenAbilityAttackHeavy = GameplayTagsManager.AddNativeGameplayTag(FName("Raven.Ability.Attack.Heavy"),
	FString("Tells the ability system that this ability is a heavy attack"));
	RavenAbilityRoll = GameplayTagsManager.AddNativeGameplayTag(FName("Raven.Ability.Roll"),
		FString("Tells the ability system that this ability is a roll"));
	RavenAbilityRoll = GameplayTagsManager.AddNativeGameplayTag(FName("Raven.Ability.Sprint"),
		FString("Tells the ability system that this ability is sprint"));

	RavenEffectDrain = GameplayTagsManager.AddNativeGameplayTag(FName("Raven.Effect.Drain"),
		FString("This tags activates infinite draining effects"));
}
