// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetController/OverlapWidgetController.h"

#include "EntitySystem/MovieSceneEntitySystemRunner.h"
#include "GAS/AuraAbilitySystemComponent.h"
#include "GAS/AuraAttributeSet.h"



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
		const FGameplayTag Message = FGameplayTag::RequestGameplayTag(FName("Message"));
			for (auto Tag : TagContainer)
			{
				if (Tag.MatchesTag(Message))
				{
					FUIWidgetRow* Row = EffectMessageDataTable.Get()->FindRow<FUIWidgetRow>(Tag.GetTagName() , TEXT(""));
					FWidgetDelegate.Broadcast(*Row);
				}
			}
	   }
	);

	if(Cast<UAuraAbilitySystemComponent>(AbilityComponent)->InitAbility == true)
	{
		OnAbilityBroadCast(Cast<UAuraAbilitySystemComponent>(AbilityComponent));
	}
	Cast<UAuraAbilitySystemComponent>(AbilityComponent)->FAbilityDelegate.BindUObject(this ,&UOverlapWidgetController::OnAbilityBroadCast);
	
}

void UOverlapWidgetController::OnAbilityBroadCast( UAuraAbilitySystemComponent* ASC)
{
	if(Cast<UAuraAbilitySystemComponent>(AbilityComponent)->InitAbility == false)return;
	const FGameplayTag Ability =  FGameplayTag::RequestGameplayTag(FName("Abilities"));
	FScopedAbilityListLock SAL(*AbilityComponent.Get());
	for(auto AbilitySpec :  ASC->GetActivatableAbilities())
	{
		if(AbilitySpec.Ability.Get()->AbilityTags.HasTag(Ability))
		{
			FGameplayTag AbTag = UAuraAbilitySystemComponent::GetAbilityTag(AbilitySpec);
			FAbilityInfo AInfo = AbilityInfos.Get()->FIndAbilityInfoWithTag(AbTag);
			for(auto tag : AbilitySpec.DynamicAbilityTags)
				if(tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Input"))))
				{
					AInfo.InputTag = tag;
					break;
				}
			AbilitiyInfoDelegate.Broadcast(AInfo);
		}
	}
}

