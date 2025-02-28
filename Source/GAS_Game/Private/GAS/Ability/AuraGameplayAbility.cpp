// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Ability/AuraGameplayAbility.h"
#include "AuraBlueprintFunctionLibrary.h"

FString UAuraGameplayAbility::GetLevelDescription(int32 Level)
{
	return FString();
}

FString UAuraGameplayAbility::GetNextLevelDescription(int32 NextLevel)
{
	return FString();
}

FString UAuraGameplayAbility::GetLockedDescription( UObject * WorldContext ,const FGameplayTag& AbilityTag)
{
	int32 Level = UAuraBlueprintFunctionLibrary::GetAbilityInfo(WorldContext)->FIndAbilityInfoWithTag(AbilityTag).OpenLevel;
	return FString::Printf(TEXT("<TEXT>UnLock Level: </><Level>%d</>\n<TEXT>Please Up Your Level</>") , Level);
}
