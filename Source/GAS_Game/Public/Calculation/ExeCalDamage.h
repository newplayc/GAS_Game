// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/AuraAttributeSet.h"
#include "GameplayEffectExecutionCalculation.h"
#include "ExeCalDamage.generated.h"

struct CaptureDefinitionStatic
{

	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitResistance);
	CaptureDefinitionStatic()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, ArmorPenetration , Source , false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Armor , Target , false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, BlockChance , Target , false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CriticalHitChance , Source , false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CriticalHitResistance , Target , false);
	}
	
};

static const CaptureDefinitionStatic GetDefinitionStatic()
{
	static CaptureDefinitionStatic captureDefinitionStatic;
	return captureDefinitionStatic;
}

/**
 * 
 */
UCLASS()
class GAS_GAME_API UExeCalDamage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
	
public:
	UExeCalDamage();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
	
};
