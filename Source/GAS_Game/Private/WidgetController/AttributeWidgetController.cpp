// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetController/AttributeWidgetController.h"

#include "GAS/AuraAbilitySystemComponent.h"
#include "GAS/AuraAttributeSet.h"
#include "PlayerState/AuraPlayerState.h"


void UAttributeWidgetController::BroadcastInitailvalues()
{

	check(AttributeInfoData); 

	for (auto& Pair : GetAuraAttriute()->TagsToAttributes)
	{
		FAttributeInfos Att = AttributeInfoData->FindAttributeInfo(Pair.Key);
		Att.Value = Pair.Value().GetNumericValue(GetAuraAttriute());
		FAttributeDelegate.Broadcast(Att);
	}
}



void UAttributeWidgetController::BindCallbacksToDependences()
{

	check(AttributeInfoData);
	GetAuraPlayerState()->OnTalentPointsChnagePs.AddDynamic(this , &UAttributeWidgetController::OnTalentPointsChanegd);
	for (auto& Pair : GetAuraAttriute()->TagsToAttributes)
	{
		AbilityComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda([this , Pair](const FOnAttributeChangeData& Data)
			{
				FAttributeInfos  Att = AttributeInfoData->FindAttributeInfo(Pair.Key);
				Att.Value = Pair.Value().GetNumericValue(GetAuraAttriute());
				FAttributeDelegate.Broadcast(Att);
			}
		);

	}
}


void UAttributeWidgetController::OnTalentPointsChanegd(int32 TalentPoints)
{
	OnTalentChangedDelegate.Broadcast(TalentPoints);
}


void UAttributeWidgetController::AddAtttribute(const FGameplayTag& AttributeTag)
{
	GetAuraASC()->AddAttribute(AttributeTag);
}
