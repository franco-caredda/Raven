// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Pickup.h"
#include "Actor/Weapon/WeaponBase.h"

#include "Component/WeaponHandlerComponent.h"

#include "Interface/WeaponHandler.h"

APickup::APickup()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APickup::Interact_Implementation(AActor* Causer)
{
	if (IWeaponHandler* WeaponHandler = Cast<IWeaponHandler>(Causer))
	{
		AWeaponBase* Weapon = GetWorld()->SpawnActor<AWeaponBase>(WeaponClass);
		UWeaponHandlerComponent* WeaponHandlerComponent = WeaponHandler->GetWeaponHandlerComponent();

		WeaponHandlerComponent->PutWeapon(Weapon);
		
		Destroy();
	}
}

void APickup::BeginPlay()
{
	Super::BeginPlay();
	
}
