// Fill out your copyright notice in the Description page of Project Settings.


#include "RavenAssetManager.h"

#include "RavenGameplayTagRegistry.h"


URavenAssetManager& URavenAssetManager::Get()
{
	check(GEngine);
	return *Cast<URavenAssetManager>(GEngine->AssetManager);
}

void URavenAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FRavenGameplayTagRegistry::Get().InitRegistry();
}
