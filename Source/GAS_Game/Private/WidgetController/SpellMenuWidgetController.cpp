// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetController/SpellMenuWidgetController.h"

#include "AuraBlueprintFunctionLibrary.h"
#include "GAS/AuraAbilitySystemComponent.h"
#include "GAS/Ability/AuraGameplayAbility.h"
#include "PlayerState/AuraPlayerState.h"

void USpellMenuWidgetController::BindCallbacksToDependences()
{
	GetAuraPlayerState()->OnSpellPointsChangePs.AddDynamic(this , &USpellMenuWidgetController::OnSpellPointChange);
}

void USpellMenuWidgetController::AddSpellLevel(const FGameplayTag & AbilityTag)
{
	if(GetAuraASC())
	{
		GetAuraASC()->ServerUpdateSpell(AbilityTag);
	}
}

void USpellMenuWidgetController::ClickSpellButtonShowDescription(const FGameplayTag AbilityTag)
{
	if(!AbilityTag.IsValid())return;
	FAbilityInfo AbilityInfo = UAuraBlueprintFunctionLibrary::GetAbilityInfo(this)->FIndAbilityInfoWithTag(AbilityTag);

	/** 当前技能已经激活  */
	if(FGameplayAbilitySpec * AbilitySpec = GetAuraASC()->FindSpecWithTag(AbilityTag))
	{
		if(UAuraGameplayAbility * Ability = Cast<UAuraGameplayAbility>(AbilitySpec->Ability.Get()))
		{
			
			FString NowLevelDes = Ability->GetLevelDescription(AbilitySpec->Level);
			FString NextLevelDes = Ability->GetNextLevelDescription(AbilitySpec->Level);
			UAuraBlueprintFunctionLibrary::GetOverlayWidgetController(this)->ShowSpellDescriptionDelegate.Broadcast(NowLevelDes , NextLevelDes);
		}
	}
	/** 还未激活查看激活条件*/
	else
	{
		FString UnLockDes = UAuraGameplayAbility::GetLockedDescription(this ,  AbilityTag);
		UAuraBlueprintFunctionLibrary::GetOverlayWidgetController(this)->ShowSpellDescriptionDelegate.Broadcast(UnLockDes , FString());
	}
	
}

void USpellMenuWidgetController::OnSpellPointChange(int32 SpellPoints)
{
	OnSpellChange.Broadcast(SpellPoints);
}
