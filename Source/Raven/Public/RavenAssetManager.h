// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "RavenAssetManager.generated.h"

UCLASS()
class RAVEN_API URavenAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:
	static URavenAssetManager& Get();
protected:
	virtual void StartInitialLoading() override;
};
