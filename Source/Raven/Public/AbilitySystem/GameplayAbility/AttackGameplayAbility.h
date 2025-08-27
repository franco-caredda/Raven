// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/GameplayAbility/RavenGameplayAbility.h"
#include "AttackGameplayAbility.generated.h"

struct FMontageDefinition;
/**
 * 
 */
UCLASS()
class RAVEN_API UAttackGameplayAbility : public URavenGameplayAbility
{
	GENERATED_BODY()
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
private:
	UFUNCTION()
	void OnMontageLoaded(UAnimMontage* AnimMontage);

	UFUNCTION()
	void OnFailed();

	UFUNCTION()
	void OnMontageCompleted();
	
	const FMontageDefinition* GetAssetDefinition(AActor* AvatarActor) const;
protected:
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag ActionTag;
private:
	const FMontageDefinition* AssetDefinition;
	
	UPROPERTY()
	TObjectPtr<UAnimMontage> SolvedAttackAnimMontage;

	int CurrentSection = -1;
};
