// Fill out your copyright notice in the Description page of Project Settings.


#include "OverlapWidgetController.h"
#include "AuraAttributeSet.h"



void UOverlapWidgetController::BroadcastInitailvalues()
{
	OnHealthChanged.Broadcast(Cast<UAuraAttributeSet>(AttributeSet)->GetHealth());
	OnMaxHealthChanged.Broadcast(Cast<UAuraAttributeSet>(AttributeSet)->GetMaxHealth());
	OnManaChanged.Broadcast(Cast<UAuraAttributeSet>(AttributeSet)->GetMana());
	OnMaxManaChanged.Broadcast(Cast<UAuraAttributeSet>(AttributeSet)->GetMaxMana());
}

void UOverlapWidgetController::BindCallbacksToDependences()
{
	UAuraAttributeSet* Attribute = CastChecked<UAuraAttributeSet>(AttributeSet);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(Attribute->GetHealthAttribute()).AddUObject(this,&UOverlapWidgetController::OnHealthChangeCallback);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(Attribute->GetMaxHealthAttribute()).AddUObject(this, &UOverlapWidgetController::OnMaxHealthChangeCallback);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(Attribute->GetManaAttribute()).AddUObject(this, &UOverlapWidgetController::OnManaChangeCallback);
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(Attribute->GetMaxManaAttribute()).AddUObject(this, &UOverlapWidgetController::OnMaxManaChangeCallback);
}

void UOverlapWidgetController::OnHealthChangeCallback(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlapWidgetController::OnMaxHealthChangeCallback(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlapWidgetController::OnManaChangeCallback(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlapWidgetController::OnMaxManaChangeCallback(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}
