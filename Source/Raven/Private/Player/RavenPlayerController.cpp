// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RavenPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

#include "InputMappingContext.h"
#include "InputAction.h"
#include "InputActionValue.h"

#include "GameFramework/Character.h"

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
	
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this,
		&ARavenPlayerController::OnJumpActionStarted);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this,
		&ARavenPlayerController::OnJumpActionCompleted);

	EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this,
		&ARavenPlayerController::OnSprintActionStarted);
	EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this,
		&ARavenPlayerController::OnSprintActionCompleted);

	EnhancedInputComponent->BindAction(DodgeAction, ETriggerEvent::Triggered, this,
		&ARavenPlayerController::OnDodgeActionTriggered);
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

void ARavenPlayerController::OnSprintActionStarted(const FInputActionValue& Value)
{
}

void ARavenPlayerController::OnSprintActionCompleted(const FInputActionValue& Value)
{
}

void ARavenPlayerController::OnDodgeActionTriggered(const FInputActionValue& Value)
{
}
