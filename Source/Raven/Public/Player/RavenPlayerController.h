// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RavenPlayerController.generated.h"

class UAbilityBufferComponent;
class URavenAbilitySystemComponent;
class UInputMappingContext;
class UInputAction;
class UAbilityInputMappingDataAsset;

struct FInputActionValue;
struct FGameplayTag;

struct FAbilityInputMapping;

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

	UFUNCTION()
	void OnMoveActionTriggered(const FInputActionValue& Value);

	UFUNCTION()
	void OnLookActionTriggered(const FInputActionValue& Value);

	UFUNCTION()
	void OnInteractActionTriggered(const FInputActionValue& Value);

	UFUNCTION()
	void OnAbilityActionStarted(FAbilityInputMapping InputMapping);

	UFUNCTION()
	void OnAbilityActionTriggered(FAbilityInputMapping InputMapping);
	
	UFUNCTION()
	void OnAbilityActionCompleted(FAbilityInputMapping InputMapping);
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
	TObjectPtr<UAbilityInputMappingDataAsset> AbilityInputMapping;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UAbilityBufferComponent> AbilityBufferComponent;
private:
	UPROPERTY()
	TObjectPtr<URavenAbilitySystemComponent> AbilitySystemComponent;
};
