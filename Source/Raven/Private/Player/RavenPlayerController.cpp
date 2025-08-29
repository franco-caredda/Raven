// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RavenPlayerController.h"
#include "Player/RavenPlayerState.h"

#include "AbilitySystem/RavenAbilitySystemComponent.h"

#include "Character/RavenCharacterPlayable.h"

#include "DataAsset/RavenGameplayAbilityDataAsset.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

#include "InputAction.h"
#include "InputActionValue.h"
#include "Component/AbilityBufferComponent.h"


ARavenPlayerController::ARavenPlayerController()
{
	AbilityBufferComponent = CreateDefaultSubobject<UAbilityBufferComponent>(TEXT("AbilityBufferComponent"));
}

void ARavenPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (InputSubsystem)
	{
		InputSubsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	ARavenPlayerState* aPlayerState = GetPlayerState<ARavenPlayerState>();
	
	AbilitySystemComponent =
		Cast<URavenAbilitySystemComponent>(aPlayerState->GetAbilitySystemComponent());
	AbilityBufferComponent->OnAbilityInputTryExecute.BindUObject(AbilitySystemComponent,
		&URavenAbilitySystemComponent::TryActivateAbilityByID);
}

void ARavenPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this,
		&ARavenPlayerController::OnMoveActionTriggered);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this,
		&ARavenPlayerController::OnLookActionTriggered);

	EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this,
		&ARavenPlayerController::OnInteractActionTriggered);

	for (const FRavenGameplayAbilityData& GameplayAbilityData :
		AbilityInputMapping->GetGameplayAbilityDataSet())
	{
		EnhancedInputComponent->BindAction(GameplayAbilityData.InputAction, ETriggerEvent::Started, this,
			&ARavenPlayerController::OnAbilityActionStarted, &GameplayAbilityData);
		EnhancedInputComponent->BindAction(GameplayAbilityData.InputAction, ETriggerEvent::Triggered, this,
			&ARavenPlayerController::OnAbilityActionTriggered, &GameplayAbilityData);
		EnhancedInputComponent->BindAction(GameplayAbilityData.InputAction, ETriggerEvent::Completed, this,
			&ARavenPlayerController::OnAbilityActionCompleted, &GameplayAbilityData);
	}
}

void ARavenPlayerController::OnMoveActionTriggered(const FInputActionValue& Value)
{
	const FVector2D Direction = Value.Get<FVector2D>();

	const FRotator Rotation = FRotator{ 0.0f, GetControlRotation().Yaw, 0.0f };
	const FRotationMatrix RotationMatrix = FRotationMatrix{Rotation};

	const FVector ForwardVector = RotationMatrix.GetUnitAxis(EAxis::X);
	const FVector RightVector = RotationMatrix.GetUnitAxis(EAxis::Y);

	if (APawn* aPawn = GetPawn())
	{
		aPawn->AddMovementInput(ForwardVector, Direction.Y);
		aPawn->AddMovementInput(RightVector, Direction.X);
	}
}

void ARavenPlayerController::OnLookActionTriggered(const FInputActionValue& Value)
{
	const FVector2D Direction = Value.Get<FVector2D>();

	AddPitchInput(Direction.Y);
	AddYawInput(Direction.X);
}

void ARavenPlayerController::OnInteractActionTriggered(const FInputActionValue& Value)
{
	if (ARavenCharacterPlayable* aCharacter = GetPawn<ARavenCharacterPlayable>())
	{
		aCharacter->TryInteract();
	}
}

// Notice: if an action has some modifiers on it, this method is not a suitable place for the ability activation 
void ARavenPlayerController::OnAbilityActionStarted(const FRavenGameplayAbilityData* AbilityData)
{
	AbilityBufferComponent->ExecuteOrRegisterInput(AbilitySystemComponent.Get(),
			*AbilityData, &URavenAbilitySystemComponent::HoldInputForAbilityByID);
}

void ARavenPlayerController::OnAbilityActionTriggered(const FRavenGameplayAbilityData* AbilityData)
{
}

void ARavenPlayerController::OnAbilityActionCompleted(const FRavenGameplayAbilityData* AbilityData)
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->ReleaseInputForAbilityByID(AbilityData->InputID);
	}
}
