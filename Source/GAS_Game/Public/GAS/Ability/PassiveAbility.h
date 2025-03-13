// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Ability/AuraGameplayAbility.h"
#include "PassiveAbility.generated.h"

/**
 * 
 */
UCLASS()
class GAS_GAME_API UPassiveAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()
public:
	
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect>PassiveGameplayEffect;

	void OnSpellChanged(const FGameplayTag & SPellTag, bool ActiveOrEnd);
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

protected:
	
	FActiveGameplayEffectHandle ActiveGameplayEffectHandle;

};
