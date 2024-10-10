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

	

	UPROPERTY(EditAnywhere , BlueprintReadOnly)
	TSubclassOf<UGameplayEffect>InitalPrimaryEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect>InitalSecondaryEffect;

	virtual void InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor) override;

	void AbilityActorInfoSet();

	void EffectApplied(UAbilitySystemComponent* ASC ,  const FGameplayEffectSpec& GameplayEffectSpec ,FActiveGameplayEffectHandle ActiveEffectHandle);

	void InitPrimaryAttribute();

	void InitSecondaryAttribute();

};
