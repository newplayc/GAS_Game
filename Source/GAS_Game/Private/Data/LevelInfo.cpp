// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/LevelInfo.h"
int32 ULevelInfo::FindExpForLevel(float NowExp)
{
		checkf(!LevelInfos.IsEmpty() , TEXT("LevelInfo Is Empty in GamemodeCharacterDatainfo"));
		
     	if(NowExp >= LevelInfos[LevelInfos.Num()-1].NeedExp)
     	{
     		return LevelInfos[LevelInfos.Num()-1].Level;
     	}
     	for(int i = 1; i <= LevelInfos.Num() - 1 ; i++)
     	{
     		if(NowExp >= LevelInfos[i].NeedExp && NowExp <= LevelInfos[i+1].NeedExp)
     		{
     			return NowExp==LevelInfos[i+1].NeedExp? i+1 : i;
     		}
     	}
     	return 1;
}

int32 ULevelInfo::GetAwardSpellPoints(int32 Level)
{
	return LevelInfos[Level].AwardSpellPoints;
}

int32 ULevelInfo::GetAwardTalentPoints(int32 Level)
{
	return LevelInfos[Level].AwardTalentPoints;
}


