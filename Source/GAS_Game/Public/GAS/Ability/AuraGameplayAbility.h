// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AuraGameplayAbility.generated.h"

/**
 *  提供了 激活标签 。 技能描述 
 */
UCLASS()
class GAS_GAME_API UAuraGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	// 激活标签 
	UPROPERTY(EditAnywhere)
	FGameplayTag ActiveTag;
	
	/** 先描述技能 再计算伤害  再蓝量消耗 冷却  */
	virtual FString GetLevelDescription(int32 Level);
	virtual FString GetNextLevelDescription(int32 NowLevel);
	static  FString GetLockedDescription( UObject * WorldContext ,const FGameplayTag & AbilityTag);

	
protected:
	FString SpellDescription;

	FString NextSpellDescription;
	
	float Damage;
	
	float  ManaCost;

	float CoolDown;
	
};
