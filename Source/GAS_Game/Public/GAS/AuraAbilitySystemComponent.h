// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Data/AbilitiyInfo.h"
#include "GameplayAbilities/Public/GameplayEffect.h"
#include "AuraAbilitySystemComponent.generated.h"


struct FAbilitySave;
DECLARE_MULTICAST_DELEGATE_OneParam(FGamplayAllTags, const FGameplayTagContainer);
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
	// 用于 在 客户端 被广播的委托 ，在 OverlayWidgetController 被绑定 ，目的是 在 拾取道具是 生成相应的 拾取信息。 
	FGamplayAllTags FAppliedAllTags;
	// ？？ 
	FAbilityDelegate FAbilityDelegate;
	// 用于 被动技能 停止或者开始时 通知 特效组件 和 停止技能
	FPassiveSpellChanged FOnPassiveSpellChanged;
	// ?? 
	FPassiveSpellEnd FOnPassiveEnd;

	// 当一个技能被取消 时 通知 OverlayController 的委托
	FSpellMenuChange FOnSpellAbilityChange;
	// 删除 输入
	FSpellMenuChange FOnSpellInputChange;
	//  装备 了某个技能
	FAbilityInfoDelegate FOnAbilityInfoChange;
	
	bool InitAbility = false;
	// 从 AbilitySpec 获取 AbiltiyTag
	static FGameplayTag GetSpellAbilityTag(const FGameplayAbilitySpec& AbilitySpec);
	// 用来 获取 需要存储的 技能 
	TArray<FAbilitySave> GetAbilitySaves();

	// 初始化 依靠 GE
	void ApplyEffectToInit(TSubclassOf<UGameplayEffect>&GE, float level ,UObject * Source);
	// 用于 从加载存档后  初始化角色
	void ApplyEffectToInitWithSetByCaller(TSubclassOf<UGameplayEffect>&GE, float level ,UObject * Source ,float Strength , float Vigor , float Intelligence , float Resilience);
	
	virtual void OnRep_ActivateAbilities()override;
	// 初始化
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
	// 暂时 没有使用
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
	
	// 更新 属性  通过send Event , 并且更新 次要属性
	UFUNCTION(Server,Reliable)
	void ServerUpdateAttribute(const FGameplayTag & AttributeTag);
	
	// 更新 技能   
	UFUNCTION(Server , Reliable)
	void ServerUpdateSpell(const FGameplayTag AbilityTag);

	// 从 ActivatableAbilities 里面 根据 tag 搜索一个AbilitySpec
	FGameplayAbilitySpec*  FindSpecWithTag(const FGameplayTag AbilityTag);
	
	static void GetInputTagFromSpec(const FGameplayAbilitySpec& Spec, FGameplayTagContainer& GameplayTags);
	
	static void GetAbilityTagFromSpec(FGameplayAbilitySpec& Spec, FGameplayTagContainer& AbilityContainer);

	static void GetStateTagFromSpec(const FGameplayAbilitySpec& Spec, FGameplayTagContainer& AbilityContainer);
	// 从存档中 读取了技能
	void AddAbilityFromSlot(TArray<FAbilitySave> & AbilitySaves);
	// 卸载某个能力 目的是更改 技能界面的 图标情况等
	UFUNCTION(Client ,Reliable)
	void ChangeAbility(const FGameplayTag& AbilityTag) ;
	//  卸载 某个能力 目的是更改 下面 那一栏 技能 输入栏的状态
	UFUNCTION(Client ,Reliable)
	void DeleteInput(const FGameplayTag& InputTag);
	
	UFUNCTION(Client , Reliable)
	void BroadCastAbilityInfo(const FAbilityInfo & AbilityInfo);


};
