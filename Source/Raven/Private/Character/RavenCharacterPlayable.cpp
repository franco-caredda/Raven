// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RavenCharacterPlayable.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AttributeSet/RavenAttributeSet.h"

#include "Camera/CameraComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

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

void ARavenCharacterPlayable::OnMovementSpeedChanged(const FOnAttributeChangeData& AttributeChangeData)
{
	const float NewMovementSpeed = AttributeChangeData.NewValue;
	CastChecked<UCharacterMovementComponent>(GetMovementComponent())->MaxWalkSpeed = NewMovementSpeed;
}
