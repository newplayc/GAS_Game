// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Ability/AuraGameplayAbility.h"
#include "AuraGameplayDamageAbility.generated.h"

/**
 * 
 */
UCLASS()
class GAS_GAME_API UAuraGameplayDamageAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()
public:


protected:
	UPROPERTY(EditDefaultsOnly)
	TMap<FGameplayTag, FScalableFloat> DamageTypes;
};
