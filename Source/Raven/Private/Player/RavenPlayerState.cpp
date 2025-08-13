// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RavenPlayerState.h"

#include "AbilitySystemComponent.h"

ARavenPlayerState::ARavenPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
}

UAbilitySystemComponent* ARavenPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
