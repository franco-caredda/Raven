// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Containers/Deque.h"
#include "AbilityBufferComponent.generated.h"

enum class EAbilityInputID : uint8;

DECLARE_DELEGATE_OneParam(FOnAbilityInputExecuteSignature, EAbilityInputID);
DECLARE_DELEGATE_RetVal_OneParam(bool, FOnAbilityInputTryExecuteSignature, EAbilityInputID);

USTRUCT()
struct FAbilityInput
{
	GENERATED_BODY()

	EAbilityInputID ID;
	float Timestamp;
};

// TODO: Currently this component caches everything, we don't want to cache jumps and some other actions.
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RAVEN_API UAbilityBufferComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAbilityBufferComponent();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void RegisterInput(EAbilityInputID InputID);
	void ExecuteOrRegisterInput(EAbilityInputID InputID, const FOnAbilityInputExecuteSignature& OnExecute);
protected:
	virtual void BeginPlay() override;
private:
	void ProcessBuffer();
public:
	FOnAbilityInputTryExecuteSignature OnAbilityInputTryExecute;
protected:
	UPROPERTY(EditDefaultsOnly)
	float BufferWindow = 2.0f;
private:
	TDeque<FAbilityInput> Buffer;
	bool bRegister = false;
};
