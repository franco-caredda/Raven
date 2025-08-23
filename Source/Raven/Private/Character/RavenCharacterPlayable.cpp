// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RavenCharacterPlayable.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AttributeSet/RavenAttributeSet.h"

#include "Actor/Weapon/WeaponBase.h"

#include "Camera/CameraComponent.h"

#include "Components/SphereComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interface/Interactable.h"

#include "Player/RavenPlayerState.h"

ARavenCharacterPlayable::ARavenCharacterPlayable()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = false;
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->TargetArmLength = 300.0f;
	SpringArmComponent->bUsePawnControlRotation = true;
	
	SpringArmComponent->AttachToComponent(GetRootComponent(),
		FAttachmentTransformRules::KeepRelativeTransform);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->AttachToComponent(SpringArmComponent, FAttachmentTransformRules::KeepRelativeTransform);

	InteractionVolume = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionVolume"));
	InteractionVolume->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	InteractionVolume->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void ARavenCharacterPlayable::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	ARavenPlayerState* RavenPlayerState = GetPlayerStateChecked<ARavenPlayerState>();
	AbilitySystemComponent = RavenPlayerState->GetAbilitySystemComponent();
	AttributeSet = RavenPlayerState->GetAttributeSet();
	
	AbilitySystemComponent->InitAbilityActorInfo(RavenPlayerState, this);

	URavenAttributeSet* RavenAttributeSet = CastChecked<URavenAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		RavenAttributeSet->GetMovementSpeedAttribute()).AddUObject(this,
			&ARavenCharacterPlayable::OnMovementSpeedChanged);
	
	GrantDefaultAbilities();
	InitEffects();
}

void ARavenCharacterPlayable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UCharacterMovementComponent* CharacterMovementComponent = GetCharacterMovement();
	CharacterMovementComponent->bOrientRotationToMovement = CharacterMovementComponent->IsMovingOnGround();
}

void ARavenCharacterPlayable::AttachWeapon_Implementation(AWeaponBase* Weapon)
{
	Execute_DetachWeapon(this);

	AttachedWeapon = Weapon;
	AttachedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale,
		WeaponAttachmentSocket);
}

void ARavenCharacterPlayable::DetachWeapon_Implementation()
{
	if (AttachedWeapon)
	{
		AttachedWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		AttachedWeapon = nullptr;
	}
}

void ARavenCharacterPlayable::TryInteract()
{
	if (Interactable)
	{
		IInteractable::Execute_Interact(Interactable.GetObject(), this);
	}
}

void ARavenCharacterPlayable::BeginPlay()
{
	Super::BeginPlay();

	InteractionVolume->OnComponentBeginOverlap.AddDynamic(this,
		&ARavenCharacterPlayable::OnInteractionVolumeBeginOverlap);
	InteractionVolume->OnComponentEndOverlap.AddDynamic(this,
		&ARavenCharacterPlayable::OnInteractionVolumeEndOverlap);
}

void ARavenCharacterPlayable::OnMovementSpeedChanged(const FOnAttributeChangeData& AttributeChangeData)
{
	const float NewMovementSpeed = AttributeChangeData.NewValue;
	CastChecked<UCharacterMovementComponent>(GetMovementComponent())->MaxWalkSpeed = NewMovementSpeed;
}

void ARavenCharacterPlayable::OnInteractionVolumeBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	Interactable = OtherActor;
}

void ARavenCharacterPlayable::OnInteractionVolumeEndOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Interactable = nullptr;
}
