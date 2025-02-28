// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilities/Public/GameplayEffect.h"
#include "AuraAbilitySystemComponent.generated.h"


DECLARE_MULTICAST_DELEGATE_OneParam(FGamplayAllTags,const  FGameplayTagContainer);
DECLARE_DELEGATE(FAbilityDelegate);

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

	FAbilityDelegate FAbilityDelegate;

	bool InitAbility = false;
	
	static FGameplayTag GetSpellAbilityTag(const FGameplayAbilitySpec& AbilitySpec);

	
	void ApplyEffectToInit(TSubclassOf<UGameplayEffect>&GE, float level ,UObject * Source);

	virtual void OnRep_ActivateAbilities()override;

	virtual void InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor) override;

	
	void AbilityActorInfoSet();


	UFUNCTION(Client , Reliable)
	void ClientEffectApplied(UAbilitySystemComponent* ASC ,  const FGameplayEffectSpec& GameplayEffectSpec ,FActiveGameplayEffectHandle ActiveEffectHandle);
	

	void GiveAbilitiesArray(TArray<TSubclassOf<UGameplayAbility>>& Abilities);
	
	void GiveBaseAbilitiesArray(TArray<TSubclassOf<UGameplayAbility>>& Abilities);
	
	void PressFunction(FGameplayTag ActionTag);
	
	void ReleaseFunction(FGameplayTag ActionTag);


	void HeldFunction(FGameplayTag ActionTag);

	void AddAttribute(const FGameplayTag& AttributeTag);

	UFUNCTION(Server , Reliable)
	void AddAbilityFromSpec( const FGameplayAbilitySpec & Spec);

	UFUNCTION(Server , Reliable)
	void ActiveAbilityFromSpec(const FGameplayAbilitySpec & Spec);
	
	UFUNCTION(Server , Reliable)
	void CancelAbilityFromSpec(const FGameplayAbilitySpec & Spec);
	
	UFUNCTION(Server,Reliable)
	void ServerUpdateAttribute(const FGameplayTag & AttributeTag);

	UFUNCTION(Server , Reliable)
	void ServerUpdateSpell(const FGameplayTag AbilityTag);

	
	FGameplayAbilitySpec*  FindSpecWithTag(const FGameplayTag AbilityTag);
};
