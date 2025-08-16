// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/AbilityInputMappingDataAsset.h"

UInputAction* UAbilityInputMappingDataAsset::FindInputActionByTag(EAbilityInputID InputID)
{
	FAbilityInputMapping* InputMapping =
		InputMappings.FindByPredicate([&InputID](const FAbilityInputMapping& CurrentInputMapping)
		{
			return CurrentInputMapping.InputAction && CurrentInputMapping.MappingID == InputID;
		});

	if (InputMapping)
	{
		return InputMapping->InputAction;
	}

	return nullptr;
}
