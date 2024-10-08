// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FGamplayAllTags, FGameplayTagContainer);

/**
 * 
 */
UCLASS()
class GAS_GAME_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:

	FGamplayAllTags FAppliedAllTags;

	
	virtual void InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor) override;

	void AbilityActorInfoSet();

	void EffectApplied(UAbilitySystemComponent* ASC ,  const FGameplayEffectSpec& GameplayEffectSpec ,FActiveGameplayEffectHandle ActiveEffectHandle);
};
