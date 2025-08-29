// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/Interactable.h"
#include "Pickup.generated.h"

class AWeaponBase;

UCLASS(Abstract)
class RAVEN_API APickup : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	APickup();

	virtual void Interact_Implementation(AActor* Causer) override;
protected:
	virtual void BeginPlay() override;
protected:
	UPROPERTY(EditAnywhere, Category="Grant")
	TSubclassOf<AWeaponBase> WeaponClass;
};
