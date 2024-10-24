// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"

#include "AuraAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class GAS_GAME_API UAuraAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:
	static const UAuraAssetManager& Get();

	virtual void StartInitialLoading() override;
};
