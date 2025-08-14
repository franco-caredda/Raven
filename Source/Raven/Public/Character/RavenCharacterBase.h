// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "RavenCharacterBase.generated.h"

class URavenAttributeSet;
class UAttributeSet;
class UGameplayAbility;

struct FGameplayAbilitySpecHandle;

UCLASS()
class RAVEN_API ARavenCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ARavenCharacterBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
protected:
	virtual void GrantDefaultAbilities();
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Ability System")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Ability System")
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(EditDefaultsOnly, Category = "Ability System")
	TArray<TSubclassOf<UGameplayAbility>> DefaultGameplayAbilities;
private:
	UPROPERTY()
	TArray<FGameplayAbilitySpecHandle> GrantedAbilities;
};
