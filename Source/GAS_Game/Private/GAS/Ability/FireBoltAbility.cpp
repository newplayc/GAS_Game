// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Ability/FireBoltAbility.h"

#include "AuraBlueprintFunctionLibrary.h"
#include "Tag/AuraGameplayTags.h"


FString UFireBoltAbility::GetLevelDescription(int32 Level)
{

	SpellDescription = FString("Launch a Fire Bolt And Cause Fire Damage");

	Damage = DamageValue.GetValueAtLevel(Level);

	GetCostGameplayEffect()->Modifiers[0].ModifierMagnitude.GetStaticMagnitudeIfPossible(Level , ManaCost);

	GetCooldownGameplayEffect()->DurationMagnitude.GetStaticMagnitudeIfPossible(Level ,CoolDown);
	
	return FString::Printf(TEXT("<TEXT>%s</>\n<TEXT>Cause FireDamage: </><Damage>%f</>\n<TEXT>ManaCost: </><Mana>%f</>\n<TEXT>CoolDown: </><CoolDown>%f</>\n<TEXT>Level: </><Level>%d</>"),*SpellDescription,Damage,ManaCost,CoolDown,Level);

}


FString UFireBoltAbility::GetNextLevelDescription(int32 NowLevel)
{

	NextSpellDescription = FString("Will Cause More Fire Damage Get Some Level Will Increase Your Bolt Count");
	return FString::Printf(TEXT("<TEXT>%s</>\n<TEXT>Next Level: </><Level>%d</>"),*NextSpellDescription ,NowLevel+1);

}

