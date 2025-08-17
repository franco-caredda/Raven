// Fill out your copyright notice in the Description page of Project Settings.


#include "RavenGameplayTagRegistry.h"
#include "GameplayTagsManager.h"

FRavenGameplayTagRegistry::FRavenGameplayTagRegistry()
{
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

	RavenEffectDrainStamina = GameplayTagsManager.AddNativeGameplayTag(FName("Raven.Effect.Drain.Stamina"),
		FString("Used in the effects that have to block stamina restoring and have a continuous cost"));
}
