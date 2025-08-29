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
	
	RavenAbilityJump = GameplayTagsManager.AddNativeGameplayTag(FName("Raven.Ability.Jump"),
		FString("Jump ability"));
	RavenAbilityDodge = GameplayTagsManager.AddNativeGameplayTag(FName("Raven.Ability.Dodge"),
		FString("Dodge ability"));
	RavenAbilityLightAttack = GameplayTagsManager.AddNativeGameplayTag(FName("Raven.Ability.LightAttack"),
		FString("Light attack"));
	RavenAbilityHeavyAttack = GameplayTagsManager.AddNativeGameplayTag(FName("Raven.Ability.HeavyAttack"),
		FString("Heavy attack"));
	RavenAbilityShield = GameplayTagsManager.AddNativeGameplayTag(FName("Raven.Ability.Shield"),
		FString("Shielding"));
	RavenAbilityUse = GameplayTagsManager.AddNativeGameplayTag(FName("Raven.Ability.Use"),
		FString("Equipped items"));
	RavenAbilityBlock = GameplayTagsManager.AddNativeGameplayTag(FName("Raven.Ability.Block"),
		FString("Block abilities with this tag"));

	RavenWeaponSword = GameplayTagsManager.AddNativeGameplayTag(FName("Raven.Weapon.Sword"),
		FString("Used on weapon classes to associate assets with the weapon"));
	RavenWeaponAxe = GameplayTagsManager.AddNativeGameplayTag(FName("Raven.Weapon.Axe"),
		FString("Used on weapon classes to associate assets with the weapon"));

	RavenEffectDrainStamina = GameplayTagsManager.AddNativeGameplayTag(FName("Raven.Effect.Drain.Stamina"),
		FString("Used in the effects that have to block stamina restoring and have a continuous cost"));
	RavenEffectAbilityCancelable = GameplayTagsManager.AddNativeGameplayTag(FName("Raven.Effect.Ability.Cancelable"),
		FString("Used in Abilities' CancelAbilitiesWithTag container to cancel abilities with this tag"));
	RavenAbilityInputBuffered = GameplayTagsManager.AddNativeGameplayTag(FName("Raven.Ability.Input.Buffered"),
		FString("Indicates whether this ability is put into the buffer or no"));
}
