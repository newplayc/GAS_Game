// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Ability/AuraGameplayAbility.h"
#include "GAS/Effect/AuraGameplayEffectTypes.h"
#include "AuraGameplayDamageAbility.generated.h"

/**
 * 
 */
UCLASS()
class GAS_GAME_API UAuraGameplayDamageAbility : public UAuraGameplayAbility
{
	
	GENERATED_BODY()

protected:

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
	
	UFUNCTION(BlueprintCallable)
	void CauseDamage(AActor * Target);
};
