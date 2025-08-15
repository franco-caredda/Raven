// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RavenPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class UAbilityInputMappingDataAsset;

struct FInputActionValue;
struct FGameplayTag;

/**
 * 
 */
UCLASS()
class RAVEN_API ARavenPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UFUNCTION()
	void OnMoveActionTriggered(const FInputActionValue& Value);

	UFUNCTION()
	void OnLookActionTriggered(const FInputActionValue& Value);

	UFUNCTION()
	void OnJumpActionStarted(const FInputActionValue& Value);

	UFUNCTION()
	void OnJumpActionCompleted(const FInputActionValue& Value);

	UFUNCTION()
	void OnAbilityActionStarted(FGameplayTag GameplayTag);

	UFUNCTION()
	void OnAbilityActionTriggered(FGameplayTag GameplayTag);
	
	UFUNCTION()
	void OnAbilityActionCompleted(FGameplayTag GameplayTag);
protected:
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, Category="Input|Actions")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category="Input|Actions")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditDefaultsOnly, Category="Input|Actions")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditDefaultsOnly, Category="Input|Actions|Abilities")
	TObjectPtr<UAbilityInputMappingDataAsset> AbilityInputMapping;
};
