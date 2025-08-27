// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "TagAssetMap.generated.h"

USTRUCT(BlueprintType)
struct FMontageDefinition
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Montage")
	TSoftObjectPtr<UAnimMontage> AnimMontage;

	UPROPERTY(EditAnywhere, Category="Montage")
	TArray<FName> MontageSections;
};

/**
 * 
 */
UCLASS()
class RAVEN_API UTagAssetMap : public UDataAsset
{
	GENERATED_BODY()
public:
	const FMontageDefinition* GetAssetDefinitionByTag(const FGameplayTag& GameplayTag);
protected:
	UPROPERTY(EditDefaultsOnly)
	TMap<FGameplayTag, FMontageDefinition> AssetMap;
};
