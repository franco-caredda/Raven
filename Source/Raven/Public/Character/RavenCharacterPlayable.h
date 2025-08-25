 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/RavenCharacterBase.h"
#include "Interface/WeaponHandler.h"
#include "RavenCharacterPlayable.generated.h"

struct FOnAttributeChangeData;

class USpringArmComponent;
class UCameraComponent;
class USphereComponent;
class IInteractable;

/**
 * Characters of this class should only be possessed by Player Controller
 */
UCLASS()
class RAVEN_API ARavenCharacterPlayable : public ARavenCharacterBase, public IWeaponHandler
{
	GENERATED_BODY()
public:
	ARavenCharacterPlayable();

	virtual void PossessedBy(AController* NewController) override;
	virtual void Tick(float DeltaTime) override;
	
	virtual UWeaponHandlerComponent* GetWeaponHandlerComponent() const override;

	void TryInteract();
protected:
	virtual void BeginPlay() override;
private:
	void OnMovementSpeedChanged(const FOnAttributeChangeData& AttributeChangeData);

	UFUNCTION()
	void OnInteractionVolumeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnInteractionVolumeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnRightHandWeaponChanged(AWeaponBase* OldWeapon, AWeaponBase* NewWeapon);
protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USphereComponent> InteractionVolume;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UWeaponHandlerComponent> WeaponHandlerComponent;
	
	UPROPERTY(EditDefaultsOnly, Category="Attachments")
	FName WeaponAttachmentSocket;
private:
	UPROPERTY()
	TScriptInterface<IInteractable> Interactable;
};
