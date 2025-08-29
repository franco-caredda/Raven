// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/AnimNotify_ApplyEffect.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"

void UAnimNotify_ApplyEffect::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                      const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	AActor* Owner = MeshComp->GetOwner();

	if (IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(Owner))
	{
		UAbilitySystemComponent* AbilitySystemComponent =
			AbilitySystemInterface->GetAbilitySystemComponent();

		FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
		ContextHandle.AddSourceObject(Owner);
		
		FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(
			EffectClass, 1, ContextHandle);
		AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data);
	}
}
