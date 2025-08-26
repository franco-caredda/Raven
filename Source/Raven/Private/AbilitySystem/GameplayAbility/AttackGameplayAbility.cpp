// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GameplayAbility/AttackGameplayAbility.h"
#include "AbilitySystem/AbilityTask/AbilityTask_LoadMontage.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"

#include "Actor/Weapon/WeaponBase.h"

#include "Component/WeaponHandlerComponent.h"

#include "Interface/WeaponHandler.h"

#include "RavenGameplayTagRegistry.h"

void UAttackGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	TSoftObjectPtr<UAnimMontage> AnimMontage = GetAnimMontage(ActorInfo->AvatarActor.Get());
	
	UAbilityTask_LoadMontage* AbilityTask_LoadMontage =
		UAbilityTask_LoadMontage::WaitLoadMontage(this, AnimMontage);

	AbilityTask_LoadMontage->OnMontageLoaded.AddDynamic(this, &UAttackGameplayAbility::OnMontageLoaded);
	AbilityTask_LoadMontage->OnMontageLoadCanceled.AddDynamic(this, &UAttackGameplayAbility::OnFailed);
	AbilityTask_LoadMontage->ReadyForActivation();
}

void UAttackGameplayAbility::OnMontageLoaded(UAnimMontage* AnimMontage)
{
	SolvedAttackAnimMontage = AnimMontage;
	
	UAbilityTask_PlayMontageAndWait* AbilityTask_PlayMontageAndWait =
		UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, FName{},
			SolvedAttackAnimMontage);

	AbilityTask_PlayMontageAndWait->OnCompleted.AddDynamic(this, &UAttackGameplayAbility::OnMontageCompleted);
	AbilityTask_PlayMontageAndWait->OnCancelled.AddDynamic(this, &UAttackGameplayAbility::OnFailed);
	AbilityTask_PlayMontageAndWait->OnInterrupted.AddDynamic(this, &UAttackGameplayAbility::OnFailed);
	AbilityTask_PlayMontageAndWait->ReadyForActivation();
}

void UAttackGameplayAbility::OnFailed()
{
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(),
		true, false);
}

void UAttackGameplayAbility::OnMontageCompleted()
{
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(),
			true, false);
}

TSoftObjectPtr<UAnimMontage> UAttackGameplayAbility::GetAnimMontage(AActor* AvatarActor) const
{
	const FRavenGameplayTagRegistry& GameplayTagRegistry = FRavenGameplayTagRegistry::Get();

	TSoftObjectPtr<UAnimMontage> AnimMontage;
	if (const IWeaponHandler* WeaponHandler = Cast<IWeaponHandler>(AvatarActor))
	{
		const UWeaponHandlerComponent* WeaponHandlerComponent = WeaponHandler->GetWeaponHandlerComponent();

		if (const AWeaponBase* WeaponBase = WeaponHandlerComponent->GetCurrentWeapon())
		{
			if (GetAssetTags().HasTagExact(GameplayTagRegistry.GetRavenAbilityLightAttack()))
			{
				AnimMontage = WeaponBase->GetLightAttackSeriesAnimMontage();
			}
			else
			{
				AnimMontage = WeaponBase->GetHeavyAttackAnimMontage();
			}
		}
	}

	if (AnimMontage.IsNull())
	{
		AnimMontage = AttackAnimMontage;
	}

	return AnimMontage;
}
