// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

#define DEFINE_GAMEPLAY_TAG_AND_HELPERS_ThreeParams(Root, FirstParam, SecondParam) \
	public: \
	FORCEINLINE const FGameplayTag& Get##Root##FirstParam##SecondParam() const \
	{ \
	return Root##FirstParam##SecondParam; \
	} \
	private: \
	FGameplayTag Root##FirstParam##SecondParam; \
	public:


#define DEFINE_GAMEPLAY_TAG_AND_HELPERS_FourParams(Root, FirstParam, SecondParam, ThirdParam) \
	public: \
	FORCEINLINE const FGameplayTag& Get##Root##FirstParam##SecondParam##ThirdParam() const \
	{ \
		return Root##FirstParam##SecondParam##ThirdParam; \
	} \
	private: \
	FGameplayTag Root##FirstParam##SecondParam##ThirdParam; \
	public:

/**
 * 
 */
class RAVEN_API FRavenGameplayTagRegistry
{
public:
	static FRavenGameplayTagRegistry& Get() noexcept;
	
	void InitRegistry();

	DEFINE_GAMEPLAY_TAG_AND_HELPERS_ThreeParams(Raven, Ability, Jump)
	DEFINE_GAMEPLAY_TAG_AND_HELPERS_ThreeParams(Raven, Ability, Dodge)
	DEFINE_GAMEPLAY_TAG_AND_HELPERS_ThreeParams(Raven, Ability, LightAttack)
	DEFINE_GAMEPLAY_TAG_AND_HELPERS_ThreeParams(Raven, Ability, HeavyAttack)
	DEFINE_GAMEPLAY_TAG_AND_HELPERS_ThreeParams(Raven, Ability, Shield)
	DEFINE_GAMEPLAY_TAG_AND_HELPERS_ThreeParams(Raven, Ability, Use)

	DEFINE_GAMEPLAY_TAG_AND_HELPERS_ThreeParams(Raven, Weapon, Sword)
	DEFINE_GAMEPLAY_TAG_AND_HELPERS_ThreeParams(Raven, Weapon, Axe)

	DEFINE_GAMEPLAY_TAG_AND_HELPERS_FourParams(Raven, Effect, Ability, Cancelable)
	DEFINE_GAMEPLAY_TAG_AND_HELPERS_FourParams(Raven, Effect, Drain, Stamina)

	DEFINE_GAMEPLAY_TAG_AND_HELPERS_FourParams(Raven, Ability, Input, Buffered)
private:
	FRavenGameplayTagRegistry();

	static FRavenGameplayTagRegistry GameplayTagRegistry;
};
