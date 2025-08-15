// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

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
	void InitRegistry();

	DEFINE_GAMEPLAY_TAG_AND_HELPERS_FourParams(Raven, Ability, Input, Jump)
	DEFINE_GAMEPLAY_TAG_AND_HELPERS_FourParams(Raven, Ability, Input, Dodge)
	DEFINE_GAMEPLAY_TAG_AND_HELPERS_FourParams(Raven, Ability, Input, LightAttack)
	DEFINE_GAMEPLAY_TAG_AND_HELPERS_FourParams(Raven, Ability, Input, HeavyAttack)
	DEFINE_GAMEPLAY_TAG_AND_HELPERS_FourParams(Raven, Ability, Input, Shield)
	DEFINE_GAMEPLAY_TAG_AND_HELPERS_FourParams(Raven, Ability, Input, Use)
private:
	FRavenGameplayTagRegistry();

	friend class URavenAssetManager;
};
