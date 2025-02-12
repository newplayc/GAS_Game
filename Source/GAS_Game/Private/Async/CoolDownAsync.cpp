// Fill out your copyright notice in the Description page of Project Settings.



#include "Async/CoolDownAsync.h"
#include "AbilitySystemComponent.h"
#include "ActiveGameplayEffectHandle.h"


void UCoolDownAsync::OnTagChanged(const FGameplayTag GT, int32 Count)const
{
	if(Count==0)
	{
		CoolDownEnd.Broadcast(0.f);
	}
}

void UCoolDownAsync::OnEffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& GEC,
	FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{
	FGameplayTagContainer TagContainer;
	GEC.GetAllGrantedTags(TagContainer);

	
	if(TagContainer.HasTagExact(CoolTag))
	{
		
		FGameplayEffectQuery EffectQuery = FGameplayEffectQuery::MakeQuery_MatchAllOwningTags(CoolTag.GetSingleTagContainer());
		TArray<float> TimeRemaing =  ASC->GetActiveEffectsTimeRemaining(EffectQuery);
		CoolDownBegin.Broadcast(TimeRemaing[0]);
	}
}

UCoolDownAsync* UCoolDownAsync::CreatCoolDownAsync(UAbilitySystemComponent* ASC, const FGameplayTag CoolDownTag)
{
	UCoolDownAsync *  CoolDownAsync = NewObject<UCoolDownAsync>();
	CoolDownAsync->ASComp = ASC;
	CoolDownAsync->CoolTag  = CoolDownTag;
	
	if(!IsValid(ASC) || !CoolDownTag.IsValid())
	{
		CoolDownAsync->EndTask();
		
		return nullptr;
	}
	
	ASC->RegisterGameplayTagEvent(CoolDownTag , EGameplayTagEventType::NewOrRemoved).AddUObject(CoolDownAsync, &UCoolDownAsync::OnTagChanged);
	ASC->OnActiveGameplayEffectAddedDelegateToSelf.AddUObject(CoolDownAsync , &UCoolDownAsync::OnEffectApplied);
	return CoolDownAsync;
}

void UCoolDownAsync::EndTask()
{
	if(!IsValid(ASComp))return;
	ASComp->RegisterGameplayTagEvent(CoolTag , EGameplayTagEventType::NewOrRemoved).RemoveAll(this);
	
	SetReadyToDestroy();
	MarkAsGarbage();
}



