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