// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetController/OverlapWidgetController.h"
#include "GAS/AuraAbilitySystemComponent.h"
#include "GAS/AuraAttributeSet.h"
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
	// 某个位置被 卸载 技能栏 的情况
	Cast<UAuraAbilitySystemComponent>(AbilityComponent)->FOnSpellInputChange.AddUObject(this, &UOverlapWidgetController::DeleteInput);
	// 能力被取消 主要目的是更改 技能页面的情况 
	Cast<UAuraAbilitySystemComponent>(AbilityComponent)->FOnSpellAbilityChange.AddUObject(this, &UOverlapWidgetController::ChangeAbility);

	// 装备了 某个技能 会 同时更改 技能装备栏 和 技能 页面
	Cast<UAuraAbilitySystemComponent>(AbilityComponent)->FOnAbilityInfoChange.AddLambda([this](const FAbilityInfo& AbilityInfo)
	{
		AbilitiyInfoDelegate.Broadcast(AbilityInfo);
	});

	
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






void UOverlapWidgetController::DeleteAbilityBlueprintCall(const FGameplayTag& AbilityInput,const FGameplayTag& AbilityType)
{
	GetAuraASC()->ServerDeleteAbility(AbilityInput , AbilityType);
}



void UOverlapWidgetController::AddAbility(const FGameplayTag & SpellTag  , const FGameplayTag & InputTag)
{
	GetAuraASC()->ServerAddAbility(SpellTag , InputTag);
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
}



void UOverlapWidgetController::ChangeAbility(const FGameplayTag& AbilityTag) 
{
	FAbilityInfo AInfo = AbilityInfos.Get()->FIndAbilityInfoWithTag(AbilityTag);
	AInfo.InputTag = FGameplayTag();
	AInfo.StateTag = FAuraGameplayTags::Get().Ability_State_Eligible;
	AbilitiyInfoDelegate.Broadcast(AInfo);
}

void UOverlapWidgetController::DeleteInput(const FGameplayTag& InputTag) 
{
	FAbilityInfo AInfo;
	AInfo.InputTag = InputTag;
	AInfo.StateTag = FAuraGameplayTags::Get().Ability_State_None;
	AbilitiyInfoDelegate.Broadcast(AInfo);
}


