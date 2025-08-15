// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RavenPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

#include "InputMappingContext.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "AbilitySystem/RavenAbilitySystemComponent.h"

#include "GameFramework/Character.h"
#include "Input/AbilityInputMappingDataAsset.h"

void ARavenPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (InputSubsystem)
	{
		InputSubsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void ARavenPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this,
		&ARavenPlayerController::OnMoveActionTriggered);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this,
		&ARavenPlayerController::OnLookActionTriggered);
	
	// EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this,
	// 	&ARavenPlayerController::OnJumpActionStarted);
	// EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this,
	// 	&ARavenPlayerController::OnJumpActionCompleted);

	for (const FAbilityInputMapping& InputMapping : AbilityInputMapping->GetInputMappings())
	{
		EnhancedInputComponent->BindAction(InputMapping.InputAction, ETriggerEvent::Started, this,
			&ARavenPlayerController::OnAbilityActionStarted, InputMapping.MappingTag);
		EnhancedInputComponent->BindAction(InputMapping.InputAction, ETriggerEvent::Triggered, this,
			&ARavenPlayerController::OnAbilityActionTriggered, InputMapping.MappingTag);
		EnhancedInputComponent->BindAction(InputMapping.InputAction, ETriggerEvent::Completed, this,
			&ARavenPlayerController::OnAbilityActionCompleted, InputMapping.MappingTag);
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

void ARavenPlayerController::OnJumpActionStarted(const FInputActionValue& Value)
{
	if (ACharacter* aCharacter = GetPawn<ACharacter>())
	{
		aCharacter->Jump();
	}
}

void ARavenPlayerController::OnJumpActionCompleted(const FInputActionValue& Value)
{
	if (ACharacter* aCharacter = GetPawn<ACharacter>())
	{
		aCharacter->StopJumping();
	}
}

// Notice: if an action has some modifiers on it, this method is not a suitable place for the ability activation 
void ARavenPlayerController::OnAbilityActionStarted(FGameplayTag GameplayTag)
{
	APawn* aPawn = GetPawn();

	URavenAbilitySystemComponent* AbilitySystemComponent =
		CastChecked<URavenAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(aPawn));

	AbilitySystemComponent->HoldInputForAbilityByTag(GameplayTag);
}

void ARavenPlayerController::OnAbilityActionTriggered(FGameplayTag GameplayTag)
{
	APawn* aPawn = GetPawn();
	
	URavenAbilitySystemComponent* AbilitySystemComponent =
		CastChecked<URavenAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(aPawn));

	AbilitySystemComponent->HoldInputForAbilityByTag(GameplayTag);
}

void ARavenPlayerController::OnAbilityActionCompleted(FGameplayTag GameplayTag)
{
	APawn* aPawn = GetPawn();
	
	URavenAbilitySystemComponent* AbilitySystemComponent =
		CastChecked<URavenAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(aPawn));

	AbilitySystemComponent->ReleaseInputForAbilityByTag(GameplayTag);
}
