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

	RavenInputAttackHeavy = GameplayTagsManager.AddNativeGameplayTag(FName("Raven.Input.Attack.Heavy"),
		FString("Input tag for heavy attack"));
	RavenInputAttackLight = GameplayTagsManager.AddNativeGameplayTag(FName("Raven.Input.Attack.Light"),
		FString("Input tag for light attack"));
	RavenInputRoll = GameplayTagsManager.AddNativeGameplayTag(FName("Raven.Input.Roll"),
		FString("Input tag for roll"));
	RavenInputRoll = GameplayTagsManager.AddNativeGameplayTag(FName("Raven.Input.Sprint"),
		FString("Input tag for sprint"));
	RavenInputConsume = GameplayTagsManager.AddNativeGameplayTag(FName("Raven.Input.Consume"),
		FString("Input tag for consumption"));

	RavenEffectDrain = GameplayTagsManager.AddNativeGameplayTag(FName("Raven.Effect.Drain"),
		FString("This tags activates infinite draining effects"));
}
