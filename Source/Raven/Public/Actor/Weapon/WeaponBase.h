// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

class URavenAbilitySystemComponent;
class UGameplayEffect;
class UBoxComponent;

UCLASS(Abstract)
class RAVEN_API AWeaponBase : public AActor,
							  public IAbilitySystemInterface
{
	GENERATED_BODY()
public:	
	AWeaponBase();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	FORCEINLINE TSoftObjectPtr<UAnimMontage> GetLightAttackSeriesAnimMontage() const
	{ return LightAttackSeriesMontage; }

	FORCEINLINE TSoftObjectPtr<UAnimMontage> GetHeavyAttackAnimMontage() const
	{ return HeavyAttackMontage; }
protected:
	virtual void BeginPlay() override;
private:
	UFUNCTION()
	void OnBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnBoxComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UBoxComponent> BoxComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<URavenAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Gameplay|Combat")
	TSoftObjectPtr<UAnimMontage> LightAttackSeriesMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Gameplay|Combat")
	TSoftObjectPtr<UAnimMontage> HeavyAttackMontage;
};
