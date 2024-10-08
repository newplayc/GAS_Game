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
	GameplayEffectSpec.GetAllGrantedTags(GameplayContainer);
	FAppliedAllTags.Broadcast(GameplayContainer);
}

