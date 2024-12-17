// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
/**
 * Singleton
 */

struct FAuraGameplayTags
{
	
public:
	static const FAuraGameplayTags& Get() { return GameplayTags; }
	static void AddGameplayTag();



	FGameplayTag Attributes_Primary_Vigor;
	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Resilience;


	FGameplayTag Attributes_Secondary_Armor;
	FGameplayTag Attributes_Secondary_ArmorPenetration;
	FGameplayTag Attributes_Secondary_BlockChance;
	FGameplayTag Attributes_Secondary_CriticalHitChance;
	FGameplayTag Attributes_Secondary_CriticalHitDamage;
	FGameplayTag Attributes_Secondary_CriticalHitResistance;
	FGameplayTag Attributes_Secondary_HealthRegeneration;
	FGameplayTag Attributes_Secondary_ManaRegeneration;
	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_MaxMana;

	FGameplayTag Attributes_Vital_Health;
	FGameplayTag Attributes_Vital_Mana;


	
	/*
	 * 输入标签
	 */
	FGameplayTag Input_LMB;
	FGameplayTag Input_RMB;
	FGameplayTag Input_1;
	FGameplayTag Input_2;
	FGameplayTag Input_3;
	FGameplayTag Input_4;

	FGameplayTag Damage;
	FGameplayTag Effects_React;
	
	/*
	* 伤害类型
	*/
	FGameplayTag Attributes_DamageType_Fire;
	FGameplayTag Attributes_DamageType_Arcane;
	FGameplayTag Attributes_DamageType_Lightning;
	FGameplayTag Attributes_DamageType_Physics;

	/*
	 *抵御类型
	 */
	FGameplayTag Attributes_Resistance_FireResistance;
	FGameplayTag Attributes_Resistance_ArcaneResistance;
	FGameplayTag Attributes_Resistance_LightningResistance;
	FGameplayTag Attributes_Resistance_PhysicsResistance;

	TMap<FGameplayTag, FGameplayTag> DamageTypeToResistance;
	
private:
	static  FAuraGameplayTags GameplayTags;


};