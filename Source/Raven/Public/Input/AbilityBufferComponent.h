// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Input/AbilityInputMappingDataAsset.h"
#include "Containers/Deque.h"
#include "AbilityBufferComponent.generated.h"


DECLARE_DELEGATE_RetVal_OneParam(bool, FOnAbilityInputTryExecuteSignature, EAbilityInputID);

USTRUCT()
struct FAbilityInput
{
	GENERATED_BODY()

	EAbilityInputID ID;
	float Timestamp;
};

/**
 * Provides the input buffering functionality to the actor this component attached to.
 * Provides only one function that should be called ExecuteOrRegisterInput
 * WARNING: This is C++ only component. Can't be instantiated in blueprints
 */
UCLASS( ClassGroup=(Custom) )
class RAVEN_API UAbilityBufferComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	template<typename UserClass, typename... TArgs>
	using TExecuteSignature = void(UserClass::*)(TArgs...);
	
	UAbilityBufferComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	 * 
	 * @tparam UserClass Class the Signature method is bound to
	 * @param Class The instance of Class the Signature method is bound to
	 * @param AbilityInputMapping Input mapping that should be buffered. NOTICE: if InputMode is set to None, then the Signature callback will be called directly
	 * @param Signature a pointer to the method of the Class instance that should be called at the beginning before buffering.
	 */
	template<typename UserClass>
	void ExecuteOrRegisterInput(UserClass* Class, FAbilityInputMapping AbilityInputMapping,
		TExecuteSignature<UserClass, EAbilityInputID> Signature)
	{
		if (AbilityInputMapping.InputMode == EInputMode::None)
		{
			(Class->*Signature)(AbilityInputMapping.MappingID);
			return;
		}
		
		if (bRegister)
		{
			RegisterInput(AbilityInputMapping.MappingID);
			return;
		}

		(Class->*Signature)(AbilityInputMapping.MappingID);
		bRegister = true; 
	}
protected:
	virtual void BeginPlay() override;
private:
	void ProcessBuffer();
	void ClearBufferTimer(float DeltaTime);
	
	void RegisterInput(EAbilityInputID InputID);
public:
	FOnAbilityInputTryExecuteSignature OnAbilityInputTryExecute;
protected:
	/**
	 * Window for the input registration process
	 */
	UPROPERTY(EditDefaultsOnly)
	float BufferWindow = 2.0f;

	/**
	 * Delay for the buffer clean up
	 */
	UPROPERTY(EditDefaultsOnly)
	float ClearBufferDelay = 1.5f;
private:
	TDeque<FAbilityInput> Buffer;

	float ClearTimer = 0.0f;
	bool bRegister = false;
};
