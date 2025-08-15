// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "RavenGameplayTagRegistry.h"
#include "RavenAssetManager.generated.h"

UCLASS()
class RAVEN_API URavenAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:
	static URavenAssetManager& Get();

	FORCEINLINE const FRavenGameplayTagRegistry& GetGameplayTagRegistry() const { return GameplayTagRegistry; }
protected:
	virtual void StartInitialLoading() override;
private:
	FRavenGameplayTagRegistry GameplayTagRegistry{};
};
