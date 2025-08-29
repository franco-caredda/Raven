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

	DEFINE_GAMEPLAY_TAG_AND_HELPERS_FourParams(Raven,  Ability, Attack, Light)
	DEFINE_GAMEPLAY_TAG_AND_HELPERS_FourParams(Raven,  Ability, Attack, Heavy)
	DEFINE_GAMEPLAY_TAG_AND_HELPERS_ThreeParams(Raven, Ability, Roll)
	DEFINE_GAMEPLAY_TAG_AND_HELPERS_ThreeParams(Raven, Ability, Sprint)

	DEFINE_GAMEPLAY_TAG_AND_HELPERS_FourParams(Raven, Input, Attack, Light)
	DEFINE_GAMEPLAY_TAG_AND_HELPERS_FourParams(Raven, Input, Attack, Heavy)
	DEFINE_GAMEPLAY_TAG_AND_HELPERS_ThreeParams(Raven, Input, Roll)
	DEFINE_GAMEPLAY_TAG_AND_HELPERS_ThreeParams(Raven, Input, Sprint)
	DEFINE_GAMEPLAY_TAG_AND_HELPERS_ThreeParams(Raven, Input, Consume)
	
	DEFINE_GAMEPLAY_TAG_AND_HELPERS_ThreeParams(Raven, Effect, Drain)
private:
	FRavenGameplayTagRegistry();

	static FRavenGameplayTagRegistry GameplayTagRegistry;
};
