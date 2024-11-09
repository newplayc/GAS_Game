// Fill out your copyright notice in the Description page of Project Settings.

#include "GAS/AuraAbilitySystemGlobals.h"
#include "Gas/Effect/AuraGameplayEffectTypes.h"


FGameplayEffectContext* UAuraAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FAuraGameplayEffectContext();
}
