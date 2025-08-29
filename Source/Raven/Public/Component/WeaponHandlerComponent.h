// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponHandlerComponent.generated.h"

class AWeaponBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnWeaponChanged, AWeaponBase*, OldWeapon, AWeaponBase*, NewWeapon);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RAVEN_API UWeaponHandlerComponent : public UActorComponent
{
	GENERATED_BODY()
public:	
	UWeaponHandlerComponent();

	UFUNCTION(BlueprintCallable)
	void PutWeapon(AWeaponBase* Weapon);

	UFUNCTION(BlueprintCallable)
	void ChangeWeapon();

	UFUNCTION(BlueprintPure)
	FORCEINLINE AWeaponBase* GetCurrentWeapon() const
	{
		if (CurrentSlot < 0)
		{
			return nullptr;
		}
		
		return RightHandSlots[CurrentSlot];
	}
protected:
	virtual void BeginPlay() override;
public:
	UPROPERTY(BlueprintAssignable)
	FOnWeaponChanged OnRightHandWeaponChanged;
protected:
	UPROPERTY(EditDefaultsOnly, Category="Slot Configuration", meta=(ClampMin=1, ClampMax=3))
	int MaxSlotNumber = 2;
private:
	UPROPERTY()
	TArray<AWeaponBase*> RightHandSlots;

	int CurrentSlot = -1;
};
