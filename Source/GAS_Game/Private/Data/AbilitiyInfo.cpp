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
