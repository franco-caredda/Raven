// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interface/CombatInterface.h"
#include "GameplayAbilitySpecHandle.h"
#include "GameplayTagContainer.h"
#include "RavenCharacterBase.generated.h"


class URavenGameplayAbilityDataAsset;
class UGameplayEffect;
class URavenAttributeSet;
class UAttributeSet;
class UGameplayAbility;

enum class EAbilityInputID : uint8;

UCLASS(Abstract)
class RAVEN_API ARavenCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	ARavenCharacterBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void LightAttack() const override;
	virtual void HeavyAttack() const override;
	virtual void Block() const override;
	virtual void Parry() const override;
protected:
	void GrantDefaultAbilities();
	
	void ApplyEffect(TSubclassOf<UGameplayEffect> GameplayEffectClass);
	void InitEffects();
private:
	void ApplyDefaultEffects();
	void ActivateAbility(FGameplayAbilitySpecHandle AbilitySpecHandle) const;
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Ability System")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Ability System")
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(EditDefaultsOnly, Category = "Ability System")
	TObjectPtr<URavenGameplayAbilityDataAsset> GameplayAbilityDataAsset;
	
	UPROPERTY(EditDefaultsOnly, Category = "Ability System")
	TArray<TSubclassOf<UGameplayEffect>> DefaultGameplayEffects;
	
	UPROPERTY(EditDefaultsOnly, Category = "Ability System|Attribute Set")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributesClass;

	UPROPERTY(EditDefaultsOnly, Category = "Ability System|Attribute Set")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributesClass;

	UPROPERTY(EditDefaultsOnly, Category = "Ability System|Attribute Set")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributesClass;
private:
	TMap<FGameplayTag, FGameplayAbilitySpecHandle> GrantedAbilities;
};
