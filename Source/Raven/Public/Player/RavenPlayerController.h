// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RavenPlayerController.generated.h"

class UAbilityBufferComponent;
class URavenAbilitySystemComponent;
class URavenGameplayAbilityDataAsset;
class UInputMappingContext;
class UInputAction;

struct FInputActionValue;
struct FGameplayTag;
struct FRavenGameplayAbilityData;

/**
 * 
 */
UCLASS()
class RAVEN_API ARavenPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ARavenPlayerController();
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
	void OnMoveActionTriggered(const FInputActionValue& Value);
	void OnLookActionTriggered(const FInputActionValue& Value);
	void OnInteractActionTriggered(const FInputActionValue& Value);
	
	void OnAbilityActionStarted(const FRavenGameplayAbilityData* AbilityData);
	void OnAbilityActionTriggered(const FRavenGameplayAbilityData* AbilityData);
	void OnAbilityActionCompleted(const FRavenGameplayAbilityData* AbilityData);
protected:
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, Category="Input|Actions")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category="Input|Actions")
	TObjectPtr<UInputAction> LookAction;
	
	UPROPERTY(EditDefaultsOnly, Category="Input|Actions")
	TObjectPtr<UInputAction> InteractAction;

	UPROPERTY(EditDefaultsOnly, Category="Input|Actions|Abilities")
	TObjectPtr<URavenGameplayAbilityDataAsset> AbilityInputMapping;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UAbilityBufferComponent> AbilityBufferComponent;
private:
	UPROPERTY()
	TObjectPtr<URavenAbilitySystemComponent> AbilitySystemComponent;
};
