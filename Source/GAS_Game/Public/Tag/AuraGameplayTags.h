// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
/**
 * Singleton
 */

struct FAuraGameplayTags
{
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

	FGameplayTag Attributes_Meta_InComingExp;
	FGameplayTag Attributes_Extra_SpellPoints;
	FGameplayTag Attributes_Extra_TalentPoints;
	
	/*
	 * 输入标签
	 */
	FGameplayTag Input_LMB;
	FGameplayTag Input_RMB;
	FGameplayTag Input_1;
	FGameplayTag Input_2;
	FGameplayTag Input_3;
	FGameplayTag Input_4;
	FGameplayTag Input_P1;
	FGameplayTag Input_P2;
	
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

	
	FGameplayTag Debuff_Burn;
	FGameplayTag Debuff_ElectricShock;
	FGameplayTag Debuff_Arcane;
	
	FGameplayTag Debuff_Chance;
	FGameplayTag Debuff_Duration;
	FGameplayTag Debuff_Frequency;
	FGameplayTag Debuff_Damage;
	
	TMap<FGameplayTag, FGameplayTag> DamageTypeToResistance;
	TMap<FGameplayTag, FGameplayTag> DamageTypeToDebuff;

	FGameplayTag Attack_MeleeAttack;
	FGameplayTag Attack_RangeAttack;
	FGameplayTag Attack_Summon;
	
	FGameplayTag Montage_Attack_1;
	FGameplayTag Montage_Attack_2;
	FGameplayTag Montage_Attack_3;
	FGameplayTag Montage_Attack_4;
	FGameplayTag Montage_Attack_5;

	FGameplayTag Socket_Weapon;
	FGameplayTag Socket_LeftHand;
	FGameplayTag Socket_RightHand;
	FGameplayTag Socket_LeftTrail;
	FGameplayTag Socket_RightTrail;


	FGameplayTag Ability_Passive;
	FGameplayTag Ability_Active;
	FGameplayTag Ability_None;
	FGameplayTag Ability_Block;
	
	
	/** Active Tag*/
	FGameplayTag Ability_Fire_FireBolt;
	FGameplayTag Ability_Fire_FireWall;
	FGameplayTag Ability_Fire_FireRain;

	FGameplayTag Ability_Arcane_ArcaneArrow;
	FGameplayTag Ability_Arcane_ArcaneShield;
	FGameplayTag Ability_Arcane_ArcaneHeal;

	FGameplayTag Ability_Lightning_Flash;
	FGameplayTag Ability_Lightning_Speed;
	FGameplayTag Ability_Lightning_Link;


	
	/** Passive Tag*/
	
	FGameplayTag Ability_IncreaseCriticalChance;
	FGameplayTag Ability_IncreaseHealth;
	FGameplayTag Ability_IncreaseMana;
	FGameplayTag Ability_LifeSiphon;
	FGameplayTag Ability_ManaSiphon;
	
	FGameplayTagContainer AbilitySpellTag;

	
	FGameplayTag Ability_State_Eligible; 
	FGameplayTag Ability_State_Locked;
	FGameplayTag Ability_State_Equipped;
	FGameplayTag Ability_State_None;
	
	/*
	 *CoolDown
	 */
	FGameplayTag CoolDown_Fire_FireBolt;
	FGameplayTag CoolDown_Fire_FireRain;
	FGameplayTag CoolDown_Fire_FireWall;

	FGameplayTag CoolDown_Arcane_ArcaneArrow;
	FGameplayTag CoolDown_Arcane_ArcaneShield;
	FGameplayTag CoolDown_Arcane_ArcaneHeal;

	FGameplayTag CoolDown_Lightning_Flash;
	FGameplayTag CoolDown_Lightning_Speed;
	FGameplayTag CoolDown_Lightning_Link;


	
private:
	static  FAuraGameplayTags GameplayTags;
};

