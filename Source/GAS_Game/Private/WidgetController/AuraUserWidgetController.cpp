// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetController/AuraUserWidgetController.h"
#include "GAS/AuraAbilitySystemComponent.h"
#include "GAS/AuraAttributeSet.h"
#include "PlayerController/AuraPlayerController.h"
#include "PlayerState/AuraPlayerState.h"

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


UAuraAbilitySystemComponent* UAuraUserWidgetController::GetAuraASC()
{

	return AuraASC == nullptr ? AuraASC = Cast<UAuraAbilitySystemComponent>(AbilityComponent) : AuraASC;
}

UAuraAttributeSet* UAuraUserWidgetController::GetAuraAttriute()
{
	return AuraAttribute==nullptr? AuraAttribute = Cast<UAuraAttributeSet>(AttributeSet) : AuraAttribute;
}

AAuraPlayerController* UAuraUserWidgetController::GetAuraPlayerController()
{
	return AuraPlayerController == nullptr ? AuraPlayerController = Cast<AAuraPlayerController>(PlayerController) : AuraPlayerController;
}

AAuraPlayerState* UAuraUserWidgetController::GetAuraPlayerState()
{
	return AuraPlayerState == nullptr ? AuraPlayerState = Cast<AAuraPlayerState>(PlayerState) : AuraPlayerState;
}
