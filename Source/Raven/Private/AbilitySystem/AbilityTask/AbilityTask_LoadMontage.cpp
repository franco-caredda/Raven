// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTask/AbilityTask_LoadMontage.h"

#include "Engine/AssetManager.h"

void UAbilityTask_LoadMontage::Activate()
{
	Super::Activate();
	
	if (Montage.IsValid())
	{
		OnNotifyMontageLoaded();
		return;
	}

	FStreamableManager& StreamableManager = GEngine->AssetManager->GetStreamableManager();
	Handle = StreamableManager.RequestAsyncLoad(Montage.ToSoftObjectPath(),
		FStreamableDelegate::CreateUObject(this, &UAbilityTask_LoadMontage::OnNotifyMontageLoaded));

	if (Handle)
	{
		Handle->BindCancelDelegate(FStreamableDelegate::CreateUObject(this,
			&UAbilityTask_LoadMontage::OnNotifyMontageLoadCanceled));
	}
}

UAbilityTask_LoadMontage* UAbilityTask_LoadMontage::WaitLoadMontage(UGameplayAbility* OwningAbility,
	TSoftObjectPtr<UAnimMontage> Montage)
{
	UAbilityTask_LoadMontage* Task = NewAbilityTask<UAbilityTask_LoadMontage>(OwningAbility);
	Task->Montage = Montage;
	return Task;
}

void UAbilityTask_LoadMontage::OnDestroy(bool bInOwnerFinished)
{
	if (Handle.IsValid())
	{
		Handle->ReleaseHandle();
	}
	Super::OnDestroy(bInOwnerFinished);
}

void UAbilityTask_LoadMontage::OnNotifyMontageLoaded()
{
	UE_LOG(LogTemp, Display, TEXT("Montage [%s] has been loaded"),
		*Montage.GetAssetName());
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnMontageLoaded.Broadcast(Montage.Get());
	}
	EndTask();
}

void UAbilityTask_LoadMontage::OnNotifyMontageLoadCanceled()
{
	UE_LOG(LogTemp, Warning, TEXT("Montage [%s] has been canceled"),
		*Montage.GetAssetName());
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnMontageLoadCanceled.Broadcast();
	}
	EndTask();
}
