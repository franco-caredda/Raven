// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_LoadMontage.generated.h"

struct FStreamableHandle;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMontageLoaded, UAnimMontage*, AnimMontage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMontageLoadCanceled);

/**
 * 
 */
UCLASS()
class RAVEN_API UAbilityTask_LoadMontage : public UAbilityTask
{
	GENERATED_BODY()
public:
	virtual void Activate() override;
	
	UFUNCTION(BlueprintCallable, Category="Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UAbilityTask_LoadMontage* WaitLoadMontage(UGameplayAbility* OwningAbility,
		TSoftObjectPtr<UAnimMontage> Montage);

	virtual void OnDestroy(bool bInOwnerFinished) override;
private:
	UFUNCTION()
	void OnNotifyMontageLoaded();

	UFUNCTION()
	void OnNotifyMontageLoadCanceled();
public:
	UPROPERTY(BlueprintAssignable)
	FOnMontageLoaded OnMontageLoaded;

	UPROPERTY(BlueprintAssignable)
	FOnMontageLoadCanceled OnMontageLoadCanceled;
private:
	TSoftObjectPtr<UAnimMontage> Montage;
	TSharedPtr<FStreamableHandle> Handle;
};
