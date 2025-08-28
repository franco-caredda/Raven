// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EAbilityInputID : uint8
{
	None = 0,
	AbilityJump = 1,
	AbilityLightAttack = 2,
	AbilityHeavyAttack = 3,
	AbilityShield = 4,
	AbilityUse = 5,
	AbilityDodge = 6,
	AbilitySprint = 7,

	MAX
};

UENUM(BlueprintType)
enum class EAbilityInputMode : uint8
{
	None = 0,
	Buffered = 1,

	MAX
};
