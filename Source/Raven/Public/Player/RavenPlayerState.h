// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "RavenPlayerState.generated.h"

class URavenAbilitySystemComponent;
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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability System")
	TObjectPtr<URavenAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Ability System")
	TObjectPtr<UAttributeSet> AttributeSet;
};
