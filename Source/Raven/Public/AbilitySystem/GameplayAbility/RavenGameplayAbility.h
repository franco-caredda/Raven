// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "RavenGameplayAbility.generated.h"

struct FGameplayTag;

UENUM(BlueprintType)
enum class EAbilityInputID : uint8
{
	None = 0,
	AbilityJump = 1,
	AbilityLightAttack = 2,
	AbilityHeavyAttack = 3,
	AbilityShield = 4,
	AbilityUse = 5,
	AbilityDodge = 6,
	AbilitySprint = 7,

	MAX
};

/**
 * 
 */
UCLASS()
class RAVEN_API URavenGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	FORCEINLINE EAbilityInputID GetInputID() const { return InputID; }
protected:
	UPROPERTY(EditDefaultsOnly, Category="Input")
	EAbilityInputID InputID;
};
