// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "AuraGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class GAS_GAME_API UAuraGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	
	UPROPERTY()
	FString SlotName;

	UPROPERTY()
	int32  SlotIndex;

	UPROPERTY()
	FName PlayerStartTag;
};
