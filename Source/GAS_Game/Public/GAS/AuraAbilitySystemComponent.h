// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Data/AbilitiyInfo.h"
#include "GameplayAbilities/Public/GameplayEffect.h"
#include "AuraAbilitySystemComponent.generated.h"


DECLARE_MULTICAST_DELEGATE_OneParam(FGamplayAllTags,const  FGameplayTagContainer);
DECLARE_DELEGATE(FAbilityDelegate);
DECLARE_MULTICAST_DELEGATE_TwoParams(FPassiveSpellChanged ,const FGameplayTag& ,bool ) ; // 作用于HaloComponent;
DECLARE_MULTICAST_DELEGATE_OneParam(FPassiveSpellEnd , const FGameplayTag & ); //   作用于结束Ability;
DECLARE_MULTICAST_DELEGATE_OneParam(FSpellMenuChange , const FGameplayTag & /* InputTag Or AbilityTag*/);
DECLARE_MULTICAST_DELEGATE_OneParam(FAbilityInfoDelegate ,const FAbilityInfo & AbilityInfo);
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
	
	FPassiveSpellChanged FOnPassiveSpellChanged;
	
	FPassiveSpellEnd FOnPassiveEnd;

	FSpellMenuChange FOnSpellAbilityChange;

	FSpellMenuChange FOnSpellInputChange;

	FAbilityInfoDelegate FOnAbilityInfoChange;
	
	bool InitAbility = false;
	
	static FGameplayTag GetSpellAbilityTag(const FGameplayAbilitySpec& AbilitySpec);

	
	void ApplyEffectToInit(TSubclassOf<UGameplayEffect>&GE, float level ,UObject * Source);

	virtual void OnRep_ActivateAbilities()override;

	virtual void InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor) override;
	
	void AbilityActorInfoSet();
	
	UFUNCTION(Client , Reliable)
	void ClientEffectApplied(UAbilitySystemComponent* ASC ,  const FGameplayEffectSpec& GameplayEffectSpec ,FActiveGameplayEffectHandle ActiveEffectHandle);

	UFUNCTION(Server , Reliable)
	void ServerAddAbility(const FGameplayTag& AbilityTag , const FGameplayTag& InputTag);

	UFUNCTION(Server , Reliable)
	void ServerDeleteAbility(const FGameplayTag& AbilityInput,const FGameplayTag& AbilityType );
	
	UFUNCTION(NetMulticast, Unreliable)
	void NetMulticast_PassiveSpellChange(const FGameplayTag &SpellTag , const bool IsActive);
	
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
	
	
	UFUNCTION(Server,Reliable)
	void ServerUpdateAttribute(const FGameplayTag & AttributeTag);

	UFUNCTION(Server , Reliable)
	void ServerUpdateSpell(const FGameplayTag AbilityTag);

	
	FGameplayAbilitySpec*  FindSpecWithTag(const FGameplayTag AbilityTag);

	static void GetInputTagFromSpec(const FGameplayAbilitySpec& Spec, FGameplayTagContainer& GameplayTags);
	
	static void GetAbilityTagFromSpec(FGameplayAbilitySpec& Spec, FGameplayTagContainer& AbilityContainer);

	
	UFUNCTION(Client ,Reliable)
	void ChangeAbility(const FGameplayTag& AbilityTag) ;

	
	UFUNCTION(Client ,Reliable)
	void DeleteInput(const FGameplayTag& InputTag);

	
	UFUNCTION(Client , Reliable)
	void BroadCastAbilityInfo(const FAbilityInfo & AbilityInfo);
};
