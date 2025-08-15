// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RavenPlayerState.h"

#include "AbilitySystem/RavenAbilitySystemComponent.h"

#include "AbilitySystem/AttributeSet/RavenAttributeSet.h"

ARavenPlayerState::ARavenPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<URavenAbilitySystemComponent>("AbilitySystemComponent");
	AttributeSet = CreateDefaultSubobject<URavenAttributeSet>(TEXT("AttributeSet"));
}

UAbilitySystemComponent* ARavenPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ARavenPlayerState::BeginPlay()
{
	Super::BeginPlay();

	ApplyEffectToSelf(DefaultPrimaryAttributesClass);
	ApplyEffectToSelf(DefaultSecondaryAttributesClass);
	ApplyEffectToSelf(DefaultVitalAttributesClass);
}

void ARavenPlayerState::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> EffectClass)
{
	FGameplayEffectContextHandle GameplayEffectContextHandle = AbilitySystemComponent->MakeEffectContext();
	GameplayEffectContextHandle.AddSourceObject(this);
	GameplayEffectContextHandle.AddInstigator(this, this);
	
	FGameplayEffectSpecHandle GameplayEffectSpecHandle =
		AbilitySystemComponent->MakeOutgoingSpec(EffectClass, 1, GameplayEffectContextHandle);
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*GameplayEffectSpecHandle.Data);
}
