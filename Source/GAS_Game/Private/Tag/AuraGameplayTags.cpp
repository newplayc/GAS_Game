// Fill out your copyright notice in the Description page of Project Settings.


#include "Tag/AuraGameplayTags.h"
#include "GameplayTagsManager.h"

FAuraGameplayTags FAuraGameplayTags::GameplayTags;


void FAuraGameplayTags::AddGameplayTag()
{
	GameplayTags.Attributes_Primary_Vigor =   UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Vigor"), FString("Add MaxHealth"));
	GameplayTags.Attributes_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Strength"), FString("Add Physical Damage"));
	GameplayTags.Attributes_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Intelligence"), FString("Add Magical Damage"));
	GameplayTags.Attributes_Primary_Resilience = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Resilience"), FString("Add Armor And ArmorPenetration"));
	
	GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor"), FString("defense Damage"));
	GameplayTags.Attributes_Secondary_ArmorPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ArmorPenetration"), FString("Ignore Armor"));
	GameplayTags.Attributes_Secondary_BlockChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.BlockChance"), FString("Add Chance to BlockDamage"));
	GameplayTags.Attributes_Secondary_CriticalHitChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitChance"), FString("Add Double Damage Chance"));
	GameplayTags.Attributes_Secondary_CriticalHitDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitDamage"), FString("Add Extra Double Damage "));
	GameplayTags.Attributes_Secondary_CriticalHitResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitResistance"), FString("Sub Double Damage Chance"));
	GameplayTags.Attributes_Secondary_HealthRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.HealthRegeneration"), FString("Cure Health"));
	GameplayTags.Attributes_Secondary_ManaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ManaRegeneration"), FString("Cure Mana"));
	GameplayTags.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxHealth"), FString(" MaxHealth"));
	GameplayTags.Attributes_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxMana"), FString("MaxMana"));

	GameplayTags.Attributes_Vital_Health = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.Health"), FString("Health"));
	GameplayTags.Attributes_Vital_Mana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.Mana"), FString("Mana"));
	
	GameplayTags.Input_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.LMB"), FString("LMB"));
	GameplayTags.Input_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.RMB"), FString("RMB"));
	GameplayTags.Input_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.1"), FString("1"));
	GameplayTags.Input_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.2"), FString("2"));
	GameplayTags.Input_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.3"), FString("3"));
	GameplayTags.Input_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.4"), FString("4"));
	
	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage") , FString("Damage"));
	GameplayTags.Effects_React = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Effects.React"));
	
	GameplayTags.Attributes_DamageType_Physics = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.physics"), FString("Damage physics"));
	GameplayTags.Attributes_DamageType_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Arcane") , FString("Damage Arcane"));
	GameplayTags.Attributes_DamageType_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Fire") , FString("Damage Fire"));
	GameplayTags.Attributes_DamageType_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Lightning"), FString("Damage Lightning"));
	
	GameplayTags.Attributes_Resistance_ArcaneResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.ArcaneResistance"), FString("ArcaneResistance"));
	GameplayTags.Attributes_Resistance_FireResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.FireResistance"), FString("FireResistance"));
	GameplayTags.Attributes_Resistance_LightningResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.LightningResistance"), FString("LightningResistance"));
	GameplayTags.Attributes_Resistance_PhysicsResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.PhysicsResistance"), FString("PhysicsResistance"));
	
	GameplayTags.DamageTypeToResistance.Add(GameplayTags.Attributes_DamageType_Fire , GameplayTags.Attributes_Resistance_FireResistance);
	GameplayTags.DamageTypeToResistance.Add(GameplayTags.Attributes_DamageType_Arcane , GameplayTags.Attributes_Resistance_ArcaneResistance);
	GameplayTags.DamageTypeToResistance.Add(GameplayTags.Attributes_DamageType_Lightning , GameplayTags.Attributes_Resistance_LightningResistance);
	GameplayTags.DamageTypeToResistance.Add(GameplayTags.Attributes_DamageType_Physics	 , GameplayTags.Attributes_Resistance_PhysicsResistance);

	GameplayTags.Attributes_Meta_InComingExp = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Meta.IncomingExp"), FString("IncomExp"));
	GameplayTags.Attributes_Extra_SpellPoints = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Extra.SpellPoints") , FString("法术技能点"));
	GameplayTags.Attributes_Extra_TalentPoints = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Extra.TalentPoints") , FString("天赋点"));
	
	GameplayTags.Attack_MeleeAttack = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attack.MeleeAttack"), FString("激活 AI 近战攻击的标签"));
	GameplayTags.Attack_RangeAttack = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attack.RangeAttack") , FString("激活 AI 远程攻击"));
	GameplayTags.Attack_Summmon = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attack.Summon"), FString("激活 AI 召唤的标签"));
	/*
	 * Socket
	 */
	GameplayTags.Socket_Weapon = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Socket.Weapon"), FString("Socket Weapon"));
	GameplayTags.Socket_LeftHand = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Socket.LeftHand"), FString("Socket LeftHand"));
	GameplayTags.Socket_RightHand = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Socket.RightHand"), FString("Socket RightHand"));
	GameplayTags.Socket_LeftTrail = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Socket.LeftTrail"), FString("Socket LeftTrail"));
	GameplayTags.Socket_RightTrail = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Socket.RightTrail"), FString("Socket RightTrail"));

	/*
	 *Montage
	 */
	GameplayTags.Montage_Attack_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack_1"), FString("Montage_Attack_1"));
	GameplayTags.Montage_Attack_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack_2"), FString("Montage_Attack_2"));
	GameplayTags.Montage_Attack_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack_3"), FString("Montage_Attack_3"));
	GameplayTags.Montage_Attack_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack_4"), FString("Montage_Attack_4"));
	GameplayTags.Montage_Attack_5 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack_5"), FString("Montage_Attack_5"));

	/*
	 * Ability
	 */
	GameplayTags.Ability_Fire_FireBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Ability.Fire.FireBolt"), FString("火球能力标签"));
	GameplayTags.Ability_Fire_FireWall = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Ability.Fire.FireWall"), FString("火墙能力标签"));
	GameplayTags.Ability_Fire_FireRain = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Ability.Fire.FireRain"), FString("火雨能力标签"));
	GameplayTags.Ability_Arcane_ArcaneArrow = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Ability.Arcane.ArcaneArrow"), FString("奥术箭能力标签"));
	GameplayTags.Ability_Arcane_ArcaneShield = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Ability.Arcane.ArcaneShield"), FString("奥术盾能力标签"));
	GameplayTags.Ability_Arcane_ArcaneHeal = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Ability.Arcane.ArcaneHeal"), FString("奥术治愈能力标签"));

	GameplayTags.Ability_Lightning_Flash = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Ability.Lightning.LightningFlash"), FString("闪电闪现能力标签"));
	GameplayTags.Ability_Lightning_Speed = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Ability.Lightning.LightningSpeed"), FString("闪电速度能力标签"));
	GameplayTags.Ability_Lightning_Link = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Ability.Lightning.LightningLink"), FString("闪电链接能力标签"));
	GameplayTags.Ability_None = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Ability.Lightning.LightningLink") ,FString("空能力标签"));
	GameplayTags.AbilitySpellTag.AddTag(FGameplayTag::RequestGameplayTag("Ability.Fire"));
	GameplayTags.AbilitySpellTag.AddTag(FGameplayTag::RequestGameplayTag("Ability.Arcane"));
	GameplayTags.AbilitySpellTag.AddTag(FGameplayTag::RequestGameplayTag("Ability.Lightning"));
	/*
	 * CoolDown
	 */
	GameplayTags.CoolDown_Fire_FireBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.Fire.FireBolt"),FString("火球冷却标签"));
	GameplayTags.CoolDown_Fire_FireRain = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.Fire.FireRain"),FString("火雨冷却标签"));
	GameplayTags.CoolDown_Fire_FireWall = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.Fire.FireWall"),FString("火墙冷却标签"));

	GameplayTags.CoolDown_Arcane_ArcaneArrow = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.Arcane.ArcaneArrow"),FString("奥术箭冷却标签"));
	GameplayTags.CoolDown_Arcane_ArcaneShield = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.Arcane.ArcaneShield"),FString("奥术盾冷却标签"));
	GameplayTags.CoolDown_Arcane_ArcaneHeal = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.Arcane.ArcaneHeal") ,FString("奥术治疗冷却标签"));

	GameplayTags.CoolDown_Lightning_Flash = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.Lightning.LightningFlash"),FString("闪电闪现冷却标签"));
	GameplayTags.CoolDown_Lightning_Link = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.Lightning.LightningLink"),FString("闪电链接冷却"));
	GameplayTags.CoolDown_Lightning_Speed = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.Lightning.LightningSpeed") ,FString("闪电速度冷却标签"));



	
	

	GameplayTags.Ability_State_Eligible = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Ability.State.Eligible"),FString("能力状态解锁标签"));
	GameplayTags.Ability_State_Equipped = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Ability.State.Equipped"),FString("能力状态装备标签"));
	GameplayTags.Ability_State_None = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Ability.State.None"),FString("能力状态空标签"));
	GameplayTags.Ability_State_Locked = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Ability.State.Lock"),FString("能力状态未解锁标签"));
	


	
}

