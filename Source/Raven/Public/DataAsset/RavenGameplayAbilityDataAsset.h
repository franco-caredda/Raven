// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AbilitySystem/GameplayAbility/RavenGameplayAbilityTypes.h"
#include "GameplayTagContainer.h"
#include "RavenGameplayAbilityDataAsset.generated.h"

class UInputAction;
class URavenGameplayAbility;

USTRUCT(BlueprintType)
struct FRavenGameplayAbilityData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Ability Configuration")
	TSubclassOf<URavenGameplayAbility> GameplayAbility;
	
	UPROPERTY(EditAnywhere, Category="Input Configuration")
	FGameplayTag InputTag;
	
	UPROPERTY(EditAnywhere, Category="Input Configuration")
	UInputAction* InputAction;

	UPROPERTY(EditAnywhere, Category="Input Configuration")
	EAbilityInputMode InputMode;
};

/**
 * 
 */
UCLASS()
class RAVEN_API URavenGameplayAbilityDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	FORCEINLINE const TArray<FRavenGameplayAbilityData>& GetGameplayAbilityDataSet() const
	{ return GameplayAbilityDataSet; }
protected:
	UPROPERTY(EditDefaultsOnly)
	TArray<FRavenGameplayAbilityData> GameplayAbilityDataSet;
};
