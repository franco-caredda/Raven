// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/TagAssetMap.h"

const FMontageDefinition* UTagAssetMap::GetAssetDefinitionByTag(const FGameplayTag& GameplayTag)
{
	return AssetMap.Find(GameplayTag);
}
