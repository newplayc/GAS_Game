// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeWidgetController.h"
#include "AuraAttributeSet.h"


void UAttributeWidgetController::BroadcastInitailvalues()
{
	UAuraAttributeSet* AS = Cast<UAuraAttributeSet>(AttributeSet);
	check(AttributeInfoData);

	for (auto& Pair : AS->TagsToAttributes)
	{
		FAttributeInfos  Att = AttributeInfoData->FindAttributeInfo(Pair.Key);
		Att.Value = Pair.Value().GetNumericValue(AS);
		FAttributeDelegate.Broadcast(Att);

	}
}

void UAttributeWidgetController::BindCallbacksToDependences()
{
	UAuraAttributeSet* AS = Cast<UAuraAttributeSet>(AttributeSet);
	check(AttributeInfoData);
	for (auto& Pair : AS->TagsToAttributes)
	{
		AbilityComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda([this , Pair , AS](const FOnAttributeChangeData& Data)
			{
				FAttributeInfos  Att = AttributeInfoData->FindAttributeInfo(Pair.Key);
				Att.Value = Pair.Value().GetNumericValue(AS);
				FAttributeDelegate.Broadcast(Att);
			}
		);

	}


}
