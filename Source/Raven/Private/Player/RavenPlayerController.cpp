// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RavenPlayerController.h"
#include "Player/RavenPlayerState.h"

#include "AbilitySystem/RavenAbilitySystemComponent.h"

#include "Character/RavenCharacterPlayable.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

#include "InputAction.h"
#include "InputActionValue.h"
#include "Input/AbilityInputMappingDataAsset.h"
#include "Input/AbilityBufferComponent.h"


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

	for (const FAbilityInputMapping& InputMapping : AbilityInputMapping->GetInputMappings())
	{
		EnhancedInputComponent->BindAction(InputMapping.InputAction, ETriggerEvent::Started, this,
			&ARavenPlayerController::OnAbilityActionStarted, InputMapping);
		EnhancedInputComponent->BindAction(InputMapping.InputAction, ETriggerEvent::Triggered, this,
			&ARavenPlayerController::OnAbilityActionTriggered, InputMapping);
		EnhancedInputComponent->BindAction(InputMapping.InputAction, ETriggerEvent::Completed, this,
			&ARavenPlayerController::OnAbilityActionCompleted, InputMapping);
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
void ARavenPlayerController::OnAbilityActionStarted(FAbilityInputMapping InputMapping)
{
//	AbilitySystemComponent->HoldInputForAbilityByID(InputID);
}

void ARavenPlayerController::OnAbilityActionTriggered(FAbilityInputMapping InputMapping)
{
	if (AbilitySystemComponent)
	{
		AbilityBufferComponent->ExecuteOrRegisterInput(AbilitySystemComponent.Get(),
			InputMapping, &URavenAbilitySystemComponent::HoldInputForAbilityByID);
	}
}

void ARavenPlayerController::OnAbilityActionCompleted(FAbilityInputMapping InputMapping)
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->ReleaseInputForAbilityByID(InputMapping.MappingID);
	}
}
