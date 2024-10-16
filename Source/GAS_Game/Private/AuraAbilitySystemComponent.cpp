// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraAbilitySystemComponent.h"



void UAuraAbilitySystemComponent::InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor)
{
	Super::InitAbilityActorInfo(InOwnerActor, InAvatarActor);
	AbilityActorInfoSet();
}

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& GameplayEffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	 FGameplayTagContainer GameplayContainer;
	GameplayEffectSpec.GetAllAssetTags(GameplayContainer);
	FAppliedAllTags.Broadcast(GameplayContainer);
}

void UAuraAbilitySystemComponent::InitAttribute(UObject * Source)
{
	ApplyEffectToInit(InitalPrimaryEffect, 1 , Source);
	ApplyEffectToInit(InitalSecondaryEffect, 1 , Source);
	ApplyEffectToInit(InitalVitalEffect,1  ,Source);
}

void UAuraAbilitySystemComponent::GiveAbilitiesArray(TArray<TSubclassOf<UGameplayAbility>>& Abilities)
{
	for (auto& Abi : Abilities)
	{
		FGameplayAbilitySpec SpecA = FGameplayAbilitySpec(Abi, 1);
		GiveAbilityAndActivateOnce(SpecA);
	}
}



/**
 * Source Always is this
 */
void UAuraAbilitySystemComponent::ApplyEffectToInit(TSubclassOf<UGameplayEffect> GE, float level , UObject * Source)
{
	check(GE);
	 FGameplayEffectContextHandle ContextHandle = MakeEffectContext();

	 ContextHandle.AddSourceObject(Source);

	const FGameplayEffectSpecHandle EffectSpecHanlde = MakeOutgoingSpec(GE, level, ContextHandle);

	ApplyGameplayEffectSpecToTarget(*EffectSpecHanlde.Data.Get(), this);


}