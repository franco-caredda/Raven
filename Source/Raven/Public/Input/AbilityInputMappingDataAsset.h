// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AbilityInputMappingDataAsset.generated.h"

class UInputAction;
enum class EAbilityInputID : uint8;

USTRUCT(BlueprintType)
struct FAbilityInputMapping
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> InputAction;

	UPROPERTY(EditAnywhere)
	EAbilityInputID MappingID;
};

/**
 * 
 */
UCLASS()
class RAVEN_API UAbilityInputMappingDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	UInputAction* FindInputActionByTag(EAbilityInputID InputID);

	FORCEINLINE const TArray<FAbilityInputMapping>& GetInputMappings() const { return InputMappings; }
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FAbilityInputMapping> InputMappings;
};
