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

void UAuraAbilitySystemComponent::InitPrimaryAttribute()
{
	check(InitalPrimaryEffect);
	const FGameplayEffectContextHandle ContextHandle = MakeEffectContext();
	const FGameplayEffectSpecHandle EffectSpecHanlde = MakeOutgoingSpec(InitalPrimaryEffect , 1 , ContextHandle);
	ApplyGameplayEffectSpecToTarget(*EffectSpecHanlde.Data.Get(), this);
}

void UAuraAbilitySystemComponent::InitSecondaryAttribute()
{
	check(InitalSecondaryEffect);
	const FGameplayEffectContextHandle ContextHandle = MakeEffectContext();
	const FGameplayEffectSpecHandle EffectSpecHanlde = MakeOutgoingSpec(InitalSecondaryEffect, 1, ContextHandle);
	ApplyGameplayEffectSpecToTarget(*EffectSpecHanlde.Data.Get(), this);
}

