// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AssetInterface.generated.h"

struct FMontageDefinition;
struct FGameplayTag;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAssetInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RAVEN_API IAssetInterface
{
	GENERATED_BODY()
public:
	virtual const FMontageDefinition* GetAssetByTag(const FGameplayTag& GameplayTag) const = 0;
};
