// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/CharacterDataInfo.h"

FCharacterDifDataInfo UCharacterDataInfo::GetCharacterDataInfo(ECharacterClass CharaClass) const
{
	return CharacterInfos.FindRef(CharaClass);
}
 