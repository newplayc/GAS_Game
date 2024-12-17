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
	
}

