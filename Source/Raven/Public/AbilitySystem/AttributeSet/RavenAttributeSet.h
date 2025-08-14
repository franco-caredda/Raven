// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "RavenAttributeSet.generated.h"


struct FGameplayEffectModCallbackData;
/**
 * 
 */
UCLASS()
class RAVEN_API URavenAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
	ATTRIBUTE_ACCESSORS_BASIC(URavenAttributeSet, Health)
	ATTRIBUTE_ACCESSORS_BASIC(URavenAttributeSet, Stamina)
	ATTRIBUTE_ACCESSORS_BASIC(URavenAttributeSet, Strength)
	ATTRIBUTE_ACCESSORS_BASIC(URavenAttributeSet, MaxHealth)
	ATTRIBUTE_ACCESSORS_BASIC(URavenAttributeSet, MaxStamina)
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Vital")
	FGameplayAttributeData Health;

	UPROPERTY(BlueprintReadOnly, Category = "Vital")
	FGameplayAttributeData Stamina;

	UPROPERTY(BlueprintReadOnly, Category = "Primary")
	FGameplayAttributeData Strength;
	
	UPROPERTY(BlueprintReadOnly, Category = "Secondary")
	FGameplayAttributeData MaxHealth;

	UPROPERTY(BlueprintReadOnly, Category = "Secondary")
	FGameplayAttributeData MaxStamina;
};
