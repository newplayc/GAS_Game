// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Ability/PassiveAbility.h"
#include "AbilitySystemComponent.h"
#include "GAS/AuraAbilitySystemComponent.h"



void UPassiveAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                      const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                      const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UAuraAbilitySystemComponent * AuraAsc = static_cast<UAuraAbilitySystemComponent*>(GetAbilitySystemComponentFromActorInfo());
	check(AuraAsc);
	// 当 被动技能 被取消时 由GAS 调用
	AuraAsc->FOnPassiveSpellChanged.AddUObject(this , &UPassiveAbility::OnSpellChanged);
	
	FGameplayEffectContextHandle ContextHandle= GetAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	ContextHandle.SetAbility(this);
	
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(PassiveGameplayEffect , GetAbilityLevel() , ContextHandle);
	
	ActiveGameplayEffectHandle  = GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	
}

// 取消能力 
void UPassiveAbility::OnSpellChanged(const FGameplayTag& SPellTag, bool ActiveOrEnd)
{
	if(!ActiveOrEnd)
	if(AbilityTags.HasTagExact(SPellTag)){
		EndAbility(CurrentSpecHandle ,CurrentActorInfo ,CurrentActivationInfo ,true ,true);
	}
}

void UPassiveAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	GetAbilitySystemComponentFromActorInfo()->RemoveActiveGameplayEffect(ActiveGameplayEffectHandle);
}



