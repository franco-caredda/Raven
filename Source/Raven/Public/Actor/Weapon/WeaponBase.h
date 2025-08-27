// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Actor.h"
#include "Interface/AssetInterface.h"
#include "WeaponBase.generated.h"

struct FMontageDefinition;
class URavenAbilitySystemComponent;
class UGameplayEffect;
class UBoxComponent;
class UTagAssetMap;

UCLASS(Abstract)
class RAVEN_API AWeaponBase : public AActor,
							  public IAbilitySystemInterface,
							  public IAssetInterface
{
	GENERATED_BODY()
public:	
	AWeaponBase();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual const FMontageDefinition* GetAssetByTag(const FGameplayTag& GameplayTag) const override;
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

	UPROPERTY(EditDefaultsOnly, Category="Assets")
	TObjectPtr<UTagAssetMap> TagAssetMap;
};
