// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/WeaponHandlerComponent.h"

UWeaponHandlerComponent::UWeaponHandlerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UWeaponHandlerComponent::PutWeapon(AWeaponBase* Weapon)
{
	if (RightHandSlots.Num() != MaxSlotNumber)
	{
		RightHandSlots.Add(Weapon);
	}
	
	if (CurrentSlot < 0)
	{
		CurrentSlot = 0;
		OnRightHandWeaponChanged.Broadcast(nullptr, Weapon);
	}
}

void UWeaponHandlerComponent::ChangeWeapon()
{
	const int OldSlot = CurrentSlot;
	
	CurrentSlot++;
	CurrentSlot %= RightHandSlots.Num();

	OnRightHandWeaponChanged.Broadcast(RightHandSlots[OldSlot], RightHandSlots[CurrentSlot]);
}

void UWeaponHandlerComponent::BeginPlay()
{
	Super::BeginPlay();

	RightHandSlots.Reserve(MaxSlotNumber);
}
