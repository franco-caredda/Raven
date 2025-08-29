// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "RavenGameplayAbility.generated.h"

struct FGameplayTag;

/**
 * 
 */
UCLASS()
class RAVEN_API URavenGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	
	FORCEINLINE FGameplayTag GetInputTag() const { return InputTag; }
protected:
	UPROPERTY(EditDefaultsOnly, Category="Input")
	FGameplayTag InputTag;
};
