// Fill out your copyright notice in the Description page of Project Settings.


#include "OverlapWidgetController.h"
#include "AuraAbilitySystemComponent.h"
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

	AbilityComponent->GetGameplayAttributeValueChangeDelegate(Attribute->GetHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data) {OnHealthChanged.Broadcast(Data.NewValue);});

	AbilityComponent->GetGameplayAttributeValueChangeDelegate(Attribute->GetMaxHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data) {OnMaxHealthChanged.Broadcast(Data.NewValue); });

	AbilityComponent->GetGameplayAttributeValueChangeDelegate(Attribute->GetManaAttribute()).AddLambda([this](const FOnAttributeChangeData& Data) { OnManaChanged.Broadcast(Data.NewValue); });

	AbilityComponent->GetGameplayAttributeValueChangeDelegate(Attribute->GetMaxManaAttribute()).AddLambda([this](const FOnAttributeChangeData& Data) {OnMaxManaChanged.Broadcast(Data.NewValue); });


	Cast<UAuraAbilitySystemComponent>(AbilityComponent)->FAppliedAllTags.AddLambda([this](const FGameplayTagContainer& TagContainer) {
		for (auto Tag : TagContainer)
		{
			/*const FString S = FString::Printf(TEXT("Tag : %s "), *Tag.ToString());
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, S);*/
			const FGameplayTag Message = FGameplayTag::RequestGameplayTag(FName("Message"));

			if (Tag.MatchesTag(Message))
			{
				FUIWidgetRow* Row = EffectMessageDataTable.Get()->FindRow<FUIWidgetRow>(Tag.GetTagName() , TEXT(""));
				FWidgetDelegate.Broadcast(*Row);
				
			}

		}
	   }
	);
	
}

