// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/AbilityInputMappingDataAsset.h"

UInputAction* UAbilityInputMappingDataAsset::FindInputActionByTag(const FGameplayTag& Tag)
{
	FAbilityInputMapping* InputMapping =
		InputMappings.FindByPredicate([&Tag](const FAbilityInputMapping& InputMapping)
		{
			return InputMapping.InputAction && InputMapping.MappingTag.MatchesTagExact(Tag);
		});

	if (InputMapping)
	{
		return InputMapping->InputAction;
	}

	return nullptr;
}
