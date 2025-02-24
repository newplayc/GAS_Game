// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetController/SpellMenuWidgetController.h"

#include "GAS/AuraAbilitySystemComponent.h"
#include "PlayerState/AuraPlayerState.h"

void USpellMenuWidgetController::BindCallbacksToDependences()
{
	GetAuraPlayerState()->OnSpellPointsChangePs.AddDynamic(this , &USpellMenuWidgetController::OnSpellPointChange);
}

void USpellMenuWidgetController::OnSpellPointChange(int32 SpellPoints)
{
	OnSpellChange.Broadcast(SpellPoints);
}
