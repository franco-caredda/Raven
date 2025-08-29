// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbilitySystem/GameplayAbility/RavenGameplayAbilityTypes.h"
#include "DataAsset/RavenGameplayAbilityDataAsset.h"
#include "Containers/Deque.h"
#include "AbilityBufferComponent.generated.h"


DECLARE_DELEGATE_RetVal_OneParam(bool, FOnAbilityInputTryExecuteSignature, const FGameplayTag&);

USTRUCT()
struct FAbilityInput
{
	GENERATED_BODY()

	FGameplayTag InputTag;
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
	using TExecuteSignature = bool(UserClass::*)(TArgs...);
	
	UAbilityBufferComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	 * 
	 * @tparam UserClass Class the Signature method is bound to
	 * @param Class The instance of Class the Signature method is bound to
	 * @param AbilityData Input mapping that should be buffered. NOTICE: if InputMode is set to None, then the Signature callback will be called directly
	 * @param Signature a pointer to the method of the Class instance that should be called at the beginning before buffering.
	 */
	template<typename UserClass>
	void ExecuteOrRegisterInput(UserClass* Class, const FRavenGameplayAbilityData& AbilityData,
		TExecuteSignature<UserClass, const FGameplayTag&> Signature)
	{
		if (AbilityData.InputMode == EAbilityInputMode::None)
		{
			UE_LOG(LogTemp, Display, TEXT("Input with ID [%s] has been directly executed"),
				*AbilityData.InputTag.ToString());
			(Class->*Signature)(AbilityData.InputTag);
			return;
		}
		
		RegisterInput(AbilityData.InputTag);
	}
protected:
	virtual void BeginPlay() override;
private:
	void ProcessBuffer();
	void ClearBufferTimer(float DeltaTime);
	
	void RegisterInput(const FGameplayTag& InputTag);
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
};
