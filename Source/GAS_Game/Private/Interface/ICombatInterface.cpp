// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/ICombatInterface.h"



// 默认返回主角职业
ECharacterClass IICombatInterface::GetCharacterClass()
{
	return ECharacterClass::elementalist;
}