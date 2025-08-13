// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RavenCharacterBase.h"

ARavenCharacterBase::ARavenCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

UAbilitySystemComponent* ARavenCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

