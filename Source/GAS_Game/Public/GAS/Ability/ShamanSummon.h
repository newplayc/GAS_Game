// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Ability/AuraGameplayAbility.h"
#include "ShamanSummon.generated.h"

/**
 *  召唤物 技能 基类。
 */
UCLASS()
class GAS_GAME_API UShamanSummon : public UAuraGameplayAbility
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere , BlueprintReadOnly)
	int32 NumSummon = 1;

	UPROPERTY(EditAnywhere , BlueprintReadOnly)
	int32 SummonSpread = 90;

	UPROPERTY(EditAnywhere , BlueprintReadOnly)
	int32 MinDistance = 50;

	UPROPERTY(EditAnywhere , BlueprintReadOnly)
	int32 MaxDistance = 200;

	UPROPERTY(EditAnywhere ,BlueprintReadWrite)
	int32 MaxSummon = 3;
	
	UPROPERTY(EditAnywhere , BlueprintReadOnly)
	TSubclassOf<AActor>SummonClass;

	UFUNCTION(BlueprintCallable)
	TArray<FVector> GetSpawnLocations();
};
