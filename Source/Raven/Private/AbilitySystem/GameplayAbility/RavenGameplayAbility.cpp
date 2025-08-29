// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GameplayAbility/RavenGameplayAbility.h"
#include "AbilitySystemComponent.h"

void URavenGameplayAbility::InputPressed(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	GetAbilitySystemComponentFromActorInfo()->
		AbilityReplicatedEventDelegate(EAbilityGenericReplicatedEvent::InputPressed, Handle,
			ActivationInfo.GetActivationPredictionKey()).Broadcast();
}

void URavenGameplayAbility::InputReleased(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	GetAbilitySystemComponentFromActorInfo()->
		AbilityReplicatedEventDelegate(EAbilityGenericReplicatedEvent::InputReleased, Handle,
			ActivationInfo.GetActivationPredictionKey()).Broadcast();
}
