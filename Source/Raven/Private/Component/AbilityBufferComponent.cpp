// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/AbilityBufferComponent.h"

UAbilityBufferComponent::UAbilityBufferComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAbilityBufferComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UAbilityBufferComponent::ProcessBuffer()
{
	if (Buffer.IsEmpty())
	{
		return;
	}
	
	const auto& [InputTag, Timestamp] = Buffer.First();

	float Delta = GetWorld()->GetTimeSeconds() - Timestamp;
	if (Delta >= BufferWindow)
	{
		UE_LOG(LogTemp, Display, TEXT("Input with ID [%s] has been removed from the buffer"),
			*InputTag.ToString());
		Buffer.PopFirst();
		
		return;
	}

	if (OnAbilityInputTryExecute.IsBound() && OnAbilityInputTryExecute.Execute(InputTag))
	{
		UE_LOG(LogTemp, Display, TEXT("Input with ID [%s] has been executed"),
			*InputTag.ToString());
		Buffer.PopFirst();
	}
}

void UAbilityBufferComponent::ClearBufferTimer(float DeltaTime)
{
	ClearTimer += DeltaTime;
	if (ClearTimer >= ClearBufferDelay && !Buffer.IsEmpty())
	{
		UE_LOG(LogTemp, Display, TEXT("Clearing the buffer"));
		
		Buffer.Empty();
	}
}

void UAbilityBufferComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	ProcessBuffer();
	ClearBufferTimer(DeltaTime);
}

void UAbilityBufferComponent::RegisterInput(const FGameplayTag& InputTag)
{
	UE_LOG(LogTemp, Display, TEXT("Input with ID [%s] has been pushed to the buffer"),
			*InputTag.ToString());
	ClearTimer = 0.0f;
	Buffer.PushLast(FAbilityInput{ InputTag,
		static_cast<float>(GetWorld()->GetTimeSeconds()) });
}

