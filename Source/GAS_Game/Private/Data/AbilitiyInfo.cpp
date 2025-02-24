// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/AbilitiyInfo.h"

FAbilityInfo UAbilitiyInfo::FIndAbilityInfoWithTag(const FGameplayTag &AbilityTag)const
{
	for(auto Ab : AbilityInfos)
	{
		if(Ab.AbilityTag.MatchesTagExact(AbilityTag))
		{
			return Ab;
		}
	}
	return FAbilityInfo();
}

FAbilityInfo UAbilitiyInfo::SetAbilityStateTagWithAbilityTag(const FGameplayTag& AbilityTag, const FGameplayTag& StateTag)
{
	for(FAbilityInfo Ab : AbilityInfos)
	{
		if(Ab.AbilityTag.MatchesTagExact(AbilityTag))
		{
			Ab.StateTag = StateTag;
			return Ab;
		}
	}
	return FAbilityInfo();
}

FAbilityInfo UAbilitiyInfo::SetAbilityInputTagWithAbilityTag(const FGameplayTag& AbilityTag, const FGameplayTag& InputTag)
{
	for(FAbilityInfo Ab : AbilityInfos)
	{
		if(Ab.AbilityTag.MatchesTagExact(AbilityTag))
		{
			Ab.InputTag = InputTag;
			return Ab;
		}
	}
	return FAbilityInfo();
}
