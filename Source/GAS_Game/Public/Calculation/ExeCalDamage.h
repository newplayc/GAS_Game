// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "ExeCalDamage.generated.h"

UCLASS()
class GAS_GAME_API UExeCalDamage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
	
public:
	UExeCalDamage();
	
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
	
};