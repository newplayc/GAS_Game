// Fill out your copyright notice in the Description page of Project Settings.


#include "ICombatInterface.h"

// Add default functionality here for any IICombatInterface functions that are not pure virtual.

int32 IICombatInterface::GetPlayerLevel()
{
	return 0;
}


FVector IICombatInterface::GetWeaponSocketLocation()
{
	return FVector();
}

void IICombatInterface::Died()
{
	return;
}

