// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "RavenCharacterBase.generated.h"

class UGameplayEffect;
class URavenAttributeSet;
class UAttributeSet;
class UGameplayAbility;

struct FGameplayAbilitySpecHandle;

UCLASS(Abstract)
class RAVEN_API ARavenCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ARavenCharacterBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
protected:
	void GrantDefaultAbilities();
	
	void ApplyEffect(TSubclassOf<UGameplayEffect> GameplayEffectClass);
	void InitEffects();
private:
	void ApplyDefaultEffects();
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Ability System")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Ability System")
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(EditDefaultsOnly, Category = "Ability System")
	TArray<TSubclassOf<UGameplayAbility>> DefaultGameplayAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "Ability System")
	TArray<TSubclassOf<UGameplayEffect>> DefaultGameplayEffects;

	UPROPERTY(EditDefaultsOnly, Category = "Ability System|Attribute Set")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributesClass;

	UPROPERTY(EditDefaultsOnly, Category = "Ability System|Attribute Set")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributesClass;

	UPROPERTY(EditDefaultsOnly, Category = "Ability System|Attribute Set")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributesClass;
};
