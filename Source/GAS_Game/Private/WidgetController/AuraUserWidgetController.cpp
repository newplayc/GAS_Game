// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetController/AuraUserWidgetController.h"

void UAuraUserWidgetController::SetWidgetParamas(const FWidgetContollerParams& WCParams)
{
	PlayerState = WCParams.PlayerState;
	PlayerController = WCParams.PlayerController;
	AbilityComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void UAuraUserWidgetController::BroadcastInitailvalues()
{

}

void UAuraUserWidgetController::BindCallbacksToDependences()
{

}
