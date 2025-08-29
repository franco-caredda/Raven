// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_ApplyEffect.generated.h"


class UGameplayEffect;
/**
 * 
 */
UCLASS()
class RAVEN_API UAnimNotify_ApplyEffect : public UAnimNotify
{
	GENERATED_BODY()
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
		const FAnimNotifyEventReference& EventReference) override;
protected:
	UPROPERTY(EditInstanceOnly, Category="Effect")
	TSubclassOf<UGameplayEffect> EffectClass;
};
