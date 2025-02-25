// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetController/OverlapWidgetController.h"
#include "GAS/AuraAbilitySystemComponent.h"
#include "GAS/AuraAttributeSet.h"
#include "PlayerController/AuraPlayerController.h"
#include "PlayerState/AuraPlayerState.h"


void UOverlapWidgetController::BroadcastInitailvalues()
{
	OnHealthChanged.Broadcast(GetAuraAttriute()->GetHealth());

	OnMaxHealthChanged.Broadcast(GetAuraAttriute()->GetMaxHealth());


	OnManaChanged.Broadcast(GetAuraAttriute()->GetMana());

	OnMaxManaChanged.Broadcast(GetAuraAttriute()->GetMaxMana());
}


void UOverlapWidgetController::BindCallbacksToDependences()
{
	

	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetAuraAttriute()->GetHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data) {OnHealthChanged.Broadcast(Data.NewValue);});

	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetAuraAttriute()->GetMaxHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data) {OnMaxHealthChanged.Broadcast(Data.NewValue); });

	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetAuraAttriute()->GetManaAttribute()).AddLambda([this](const FOnAttributeChangeData& Data) { OnManaChanged.Broadcast(Data.NewValue); });

	AbilityComponent->GetGameplayAttributeValueChangeDelegate(GetAuraAttriute()->GetMaxManaAttribute()).AddLambda([this](const FOnAttributeChangeData& Data) {OnMaxManaChanged.Broadcast(Data.NewValue); });


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

	// if(GetAuraASC()->InitAbility == true)
	// {
	// 	OnAbilityBroadCast();
	// }
//	GetAuraASC()->FAbilityDelegate.BindUObject(this ,&UOverlapWidgetController::OnAbilityBroadCast);
	
	GetAuraPlayerState()->OnExpChangePs.AddDynamic(this,&UOverlapWidgetController::OnPsExpBroadCast);
	GetAuraPlayerState()->OnLevelChangePs.AddDynamic(this,&UOverlapWidgetController::OnPsLevelBroadCast);
	
	
}

void UOverlapWidgetController::OnPsExpBroadCast(int32 Exp) 
{
	
	ExpChanged.Broadcast(Exp);
}

void UOverlapWidgetController::OnPsLevelBroadCast(int32 Level)
{
	LevelChanged.Broadcast(Level);
}

void UOverlapWidgetController::OnAbilityBroadCast()
{

	if(GetAuraASC()->InitAbility == false)return;
	const FGameplayTag Ability =  FGameplayTag::RequestGameplayTag(FName("Ability"));
	for(auto AbilitySpec :  GetAuraASC()->GetActivatableAbilities())
	{
		if(AbilitySpec.Ability.Get()->AbilityTags.HasTag(Ability))
		{
			FGameplayTag AbTag = UAuraAbilitySystemComponent::GetSpellAbilityTag(AbilitySpec);
			FAbilityInfo AInfo = AbilityInfos.Get()->FIndAbilityInfoWithTag(AbTag);
			for(auto tag : AbilitySpec.DynamicAbilityTags)
			{
				if(tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Ability.State"))))
				{
					AInfo.StateTag = tag;
				}
				if(tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Input"))))
				{
					AInfo.InputTag = tag;
				}
			}
	AbilitiyInfoDelegate.Broadcast(AInfo);
		}
	}
}

void UOverlapWidgetController::GetAbilityTagFromSpec(FGameplayAbilitySpec& Spec, FGameplayTagContainer& AbilityContainer)
{
	FGameplayTagContainer AbilityTag;
	AbilityTag.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability")));
	AbilityContainer = Spec.Ability.Get()->AbilityTags.Filter(AbilityTag);
}

void UOverlapWidgetController::DeleteAbility(const FGameplayTag& AbilityInput, FGameplayAbilitySpec& Spec)
{
	Spec.DynamicAbilityTags.RemoveTag(FAuraGameplayTags::Get().Ability_State_Equipped);
	Spec.DynamicAbilityTags.AddTag(FAuraGameplayTags::Get().Ability_State_Eligible);
	Spec.DynamicAbilityTags.RemoveTag(AbilityInput);
	FGameplayTagContainer AbilityContainer;
	GetAbilityTagFromSpec(Spec, AbilityContainer);
	ChangeAbility(AbilityContainer.First());
}

void UOverlapWidgetController::DeleteAbility(const FGameplayTag& AbilityInput)
{
	for(FGameplayAbilitySpec& Spec :GetAuraASC()->GetActivatableAbilities())
	{
		if(Spec.DynamicAbilityTags.HasTagExact(AbilityInput))
		{
			Spec.DynamicAbilityTags.RemoveTag(FAuraGameplayTags::Get().Ability_State_Equipped);
			Spec.DynamicAbilityTags.AddTag(FAuraGameplayTags::Get().Ability_State_Eligible);
			Spec.DynamicAbilityTags.RemoveTag(AbilityInput);
			FGameplayTagContainer AbilityContainer;
			GetAbilityTagFromSpec(Spec, AbilityContainer);
			ChangeAbility(AbilityContainer.First());
			DeleteInput(AbilityInput);
			return;
		}
	}

}

void UOverlapWidgetController::GetInputTagFromSpec(FGameplayAbilitySpec& Spec, FGameplayTagContainer& InputContainer)
{
	FGameplayTagContainer InputTag;
	InputTag.AddTag(FGameplayTag::RequestGameplayTag(FName("Input")));
	InputContainer = Spec.DynamicAbilityTags.Filter(InputTag);
}

void UOverlapWidgetController::AddAbility_Implementation(FAbilityInfo AbilityInfo)
{
	
	AbilityInfo.StateTag = FAuraGameplayTags::Get().Ability_State_Equipped;
	bool IsPass = false;
	for(FGameplayAbilitySpec& Spec :GetAuraASC()->GetActivatableAbilities())
	{
		if(Spec.DynamicAbilityTags.HasTagExact(AbilityInfo.InputTag))
		{
			/** 当前位置有能力  先卸掉当前位置能力*/
			DeleteAbility(AbilityInfo.InputTag, Spec);
			if(IsPass)break;
			IsPass = true;
		}
		if(Spec.Ability.Get()->AbilityTags.HasTagExact(AbilityInfo.AbilityTag))
		{
			/**当前能力在其他位置上 */
			if(Spec.DynamicAbilityTags.HasTagExact(FAuraGameplayTags::Get().Ability_State_Equipped))
			{
				Spec.DynamicAbilityTags.RemoveTag(FAuraGameplayTags::Get().Ability_State_Equipped);
				FGameplayTagContainer InputContainer;
				GetInputTagFromSpec(Spec, InputContainer);
				Spec.DynamicAbilityTags.RemoveTags(InputContainer);
				DeleteInput(InputContainer.First());
			}
				Spec.DynamicAbilityTags.RemoveTag(FAuraGameplayTags::Get().Ability_State_Eligible);
				Spec.DynamicAbilityTags.AddTag(FAuraGameplayTags::Get().Ability_State_Equipped);
				Spec.DynamicAbilityTags.AddTag(AbilityInfo.InputTag);
				if(IsPass)break;
				IsPass = true;
		}
	}
	AbilitiyInfoDelegate.Broadcast(AbilityInfo);
}



void UOverlapWidgetController::LevelChangeSpell(float Level, FGameplayTag AbilityTag)
{
	
	FAbilityInfo AbilityInfo = AbilityInfos.Get()->FIndAbilityInfoWithTag(AbilityTag);
	if(GetAuraASC()->FindSpecWithTag(AbilityTag) ==nullptr)
	{
		if(AbilityInfo.OpenLevel <= Level)
		{
			AbilityInfo.StateTag = FAuraGameplayTags::Get().Ability_State_Eligible;
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityInfo.AbilityClass , 1);
			AbilitySpec.DynamicAbilityTags.AddTag(FAuraGameplayTags::Get().Ability_State_Eligible);
			GetAuraASC()->AddAbilityFromSpec(AbilitySpec);
			AbilitiyInfoDelegate.Broadcast(AbilityInfo);
		}
	}
	else
	{
		for(auto AbilitySpec : GetAuraASC()->GetActivatableAbilities())
		{
			if(AbilitySpec.Ability.Get()->AbilityTags.HasTag(AbilityTag))
			{
				
				for(auto tag : AbilitySpec.DynamicAbilityTags)
				{
					if(tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Ability.State"))))
					{
						AbilityInfo.StateTag = tag;
					}
					if(tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Input"))))
					{
						AbilityInfo.InputTag = tag;
					}
				}
				AbilitiyInfoDelegate.Broadcast(AbilityInfo);
				return;
			}
		}
	}
}

void UOverlapWidgetController::ClientBroadcastAbility_Implementation(const FAbilityInfo & AbilityInfo)
{
	
	AbilitiyInfoDelegate.Broadcast(AbilityInfo);
	
}

void UOverlapWidgetController::ChangeAbility(FGameplayTag AbilityTag)
{
	FAbilityInfo AInfo = AbilityInfos.Get()->FIndAbilityInfoWithTag(AbilityTag);
	AInfo.InputTag = FGameplayTag();
	AInfo.StateTag = FAuraGameplayTags::Get().Ability_State_Eligible;
	AbilitiyInfoDelegate.Broadcast(AInfo);
}

void UOverlapWidgetController::DeleteInput(FGameplayTag InputTag)
{
	FAbilityInfo AInfo;
	AInfo.InputTag = InputTag;
	AInfo.StateTag = FAuraGameplayTags::Get().Ability_State_None;
	AbilitiyInfoDelegate.Broadcast(AInfo);
}




