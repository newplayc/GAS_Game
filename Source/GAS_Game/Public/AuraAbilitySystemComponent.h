// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilities/Public/GameplayEffect.h"
#include "AuraAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FGamplayAllTags, FGameplayTagContainer);


class UGameplayEffect;
/**
 * 
 */
UCLASS()
class GAS_GAME_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:

	FGamplayAllTags FAppliedAllTags;

	

	void ApplyEffectToInit(TSubclassOf<UGameplayEffect>&GE, float level ,UObject * Source);


	virtual void InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor) override;


	void AbilityActorInfoSet();


	UFUNCTION(Client , Reliable)
	void ClientEffectApplied(UAbilitySystemComponent* ASC ,  const FGameplayEffectSpec& GameplayEffectSpec ,FActiveGameplayEffectHandle ActiveEffectHandle);
	

	void GiveAbilitiesArray(TArray<TSubclassOf<UGameplayAbility>>& Abilities);


	void PressFunction(FGameplayTag ActionTag);


	void ReleaseFunction(FGameplayTag ActionTag);


	void HeldFunction(FGameplayTag ActionTag);


};
