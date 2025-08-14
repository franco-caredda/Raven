// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "RavenPlayerState.generated.h"

class UGameplayEffect;
class UAttributeSet;

/**
 * 
 */
UCLASS()
class RAVEN_API ARavenPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	ARavenPlayerState();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	FORCEINLINE UAttributeSet* GetAttributeSet() const { return AttributeSet; }
protected:
	virtual void BeginPlay() override;

	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> EffectClass);
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Ability System")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Ability System")
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(EditDefaultsOnly, Category = "Ability System|Attribute Set")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributesClass;

	UPROPERTY(EditDefaultsOnly, Category = "Ability System|Attribute Set")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributesClass;

	UPROPERTY(EditDefaultsOnly, Category = "Ability System|Attribute Set")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributesClass;
};
