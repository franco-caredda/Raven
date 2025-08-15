// Fill out your copyright notice in the Description page of Project Settings.


#include "RavenGameplayTagRegistry.h"
#include "GameplayTagsManager.h"

FRavenGameplayTagRegistry::FRavenGameplayTagRegistry()
{
}

void FRavenGameplayTagRegistry::InitRegistry()
{
	UGameplayTagsManager& GameplayTagsManager = UGameplayTagsManager::Get();
	
	RavenAbilityInputJump = GameplayTagsManager.AddNativeGameplayTag(FName("Raven.Ability.Input.Jump"),
		FString("Input for the jump ability"));
	RavenAbilityInputDodge = GameplayTagsManager.AddNativeGameplayTag(FName("Raven.Ability.Input.Dodge"),
		FString("Input for the dodge ability"));
	RavenAbilityInputLightAttack = GameplayTagsManager.AddNativeGameplayTag(FName("Raven.Ability.Input.LightAttack"),
		FString("Input for the light attack"));
	RavenAbilityInputHeavyAttack = GameplayTagsManager.AddNativeGameplayTag(FName("Raven.Ability.Input.HeavyAttack"),
		FString("Input for the heavy attack"));
	RavenAbilityInputShield = GameplayTagsManager.AddNativeGameplayTag(FName("Raven.Ability.Input.Shield"),
		FString("Input for shielding"));
	RavenAbilityInputUse = GameplayTagsManager.AddNativeGameplayTag(FName("Raven.Ability.Input.Use"),
		FString("Input for using equipped items"));
}
