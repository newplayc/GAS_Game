// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Ability/AuraGameplayAbility.h"
#include "GAS/Effect/AuraGameplayEffectTypes.h"
#include "AuraGameplayDamageAbility.generated.h"

/**
 *    一个 可以 造成 伤害 技能的 基类  包含了 Debuff 相关 ， 伤害标签 ， 数值， 等等。
 */
UCLASS()
class GAS_GAME_API UAuraGameplayDamageAbility : public UAuraGameplayAbility
{
	
	GENERATED_BODY()

protected:
	// 创建 一个 EffectParams  这个结构 都是 应用技能时需要的 ， 例如 伤害 ， buff ， 目标 等等
	UFUNCTION(BlueprintCallable)
	FEffectParams MakeDefaultEffectParams(AActor* TargetActor = nullptr);
	
	UPROPERTY(EditDefaultsOnly , BlueprintReadOnly)
	TSubclassOf<UGameplayEffect>DamageEffect;
	
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag DamageTypeTag;

	UPROPERTY(EditDefaultsOnly)
	FScalableFloat DamageValue;
		
	UPROPERTY(EditDefaultsOnly)
	float DebuffDamage;

	UPROPERTY(EditDefaultsOnly)
	float DebuffDuration;
	
	UPROPERTY(EditDefaultsOnly)
	float DebuffFrenquency;

	UPROPERTY(EditDefaultsOnly)
	float DebuffChance;

	UPROPERTY(EditDefaultsOnly)
	float DeathImpulseMagnitude;

	UPROPERTY(EditDefaultsOnly)
	float KnockBackMagnitude;

	UPROPERTY(EditDefaultsOnly)
	bool bShouldKnockBack;
	
	UFUNCTION(BlueprintCallable)
	void CauseDamage(AActor * Target);
};
