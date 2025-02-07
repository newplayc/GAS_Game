
// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/AttributeInfo.h"

#include "GAS_Game/AuraLog.h"

const FAttributeInfos UAttributeInfo::FindAttributeInfo(const FGameplayTag& GameplayTag, bool IsLogNotF) const
{
	for (const FAttributeInfos& AttriInfo : AttributeInfoArray)
	{
		if (AttriInfo.GameplayTag.MatchesTagExact(GameplayTag))
		{
			return AttriInfo;
		}
	}
	if (IsLogNotF)
	{
		UE_LOG(AuraLog, Warning, TEXT("Not Found Match Tag"));
	}
	return FAttributeInfos();
}
