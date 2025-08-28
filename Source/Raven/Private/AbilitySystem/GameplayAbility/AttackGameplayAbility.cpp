// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GameplayAbility/AttackGameplayAbility.h"
#include "AbilitySystem/AbilityTask/AbilityTask_LoadMontage.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"

#include "Actor/Weapon/WeaponBase.h"

#include "Component/WeaponHandlerComponent.h"

#include "Interface/WeaponHandler.h"

#include "DataAsset/TagAssetMap.h"

void UAttackGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                             const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                             const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	AssetDefinition = GetAssetDefinition(ActorInfo->AvatarActor.Get());
	
	if (!AssetDefinition)
	{
		OnFailed();
		return;
	}

	CurrentSection++;
	CurrentSection = CurrentSection % AssetDefinition->MontageSections.Num();

	
	UAbilityTask_LoadMontage* AbilityTask_LoadMontage =
		UAbilityTask_LoadMontage::WaitLoadMontage(this, AssetDefinition->AnimMontage);

	AbilityTask_LoadMontage->OnMontageLoaded.AddDynamic(this, &UAttackGameplayAbility::OnMontageLoaded);
	AbilityTask_LoadMontage->OnMontageLoadCanceled.AddDynamic(this, &UAttackGameplayAbility::OnCanceled);
	AbilityTask_LoadMontage->ReadyForActivation();
}

void UAttackGameplayAbility::OnMontageLoaded(UAnimMontage* AnimMontage)
{
	SolvedAttackAnimMontage = AnimMontage;

	UE_LOG(LogTemp, Display, TEXT("Playing the section with index [%d]"), CurrentSection);
	
	UAbilityTask_PlayMontageAndWait* AbilityTask_PlayMontageAndWait =
		UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, FName{},
			SolvedAttackAnimMontage, 1.0f, AssetDefinition->MontageSections[CurrentSection]);

	AbilityTask_PlayMontageAndWait->OnCompleted.AddDynamic(this, &UAttackGameplayAbility::OnMontageCompleted);
	AbilityTask_PlayMontageAndWait->OnCancelled.AddDynamic(this, &UAttackGameplayAbility::OnCanceled);
	AbilityTask_PlayMontageAndWait->OnInterrupted.AddDynamic(this, &UAttackGameplayAbility::OnFailed);
	AbilityTask_PlayMontageAndWait->ReadyForActivation();
}

void UAttackGameplayAbility::OnFailed()
{
	UE_LOG(LogTemp, Display, TEXT("The ability has been terminated for some reason"));
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(),
		true, false);
}

void UAttackGameplayAbility::OnCanceled()
{
	UE_LOG(LogTemp, Display, TEXT("The ability has been canceled for some reason"));
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(),
		true, true);
}

void UAttackGameplayAbility::OnMontageCompleted()
{
	UE_LOG(LogTemp, Display, TEXT("The ability has been completed"));
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(),
			true, false);
}

const FMontageDefinition* UAttackGameplayAbility::GetAssetDefinition(AActor* AvatarActor) const
{
	if (const IWeaponHandler* WeaponHandler = Cast<IWeaponHandler>(AvatarActor))
	{
		const UWeaponHandlerComponent* WeaponHandlerComponent = WeaponHandler->GetWeaponHandlerComponent();

		if (const AWeaponBase* WeaponBase = WeaponHandlerComponent->GetCurrentWeapon())
		{
			return WeaponBase->GetAssetByTag(ActionTag);
		}
	}

	return nullptr;
}
