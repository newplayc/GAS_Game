// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AuraAbilitySystemComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AuraBlueprintFunctionLibrary.h"
#include "Character/AuraCharacter.h"
#include "GAS/AuraAttributeSet.h"
#include "GAS/Ability/AuraGameplayAbility.h"
#include "GAS_Game/AuraLog.h"
#include "Interface/PlayerInterface.h"
#include "PlayerState/AuraPlayerState.h"
#include "Tag/AuraGameplayTags.h"


void UAuraAbilitySystemComponent::InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor)
{
	Super::InitAbilityActorInfo(InOwnerActor, InAvatarActor);
	AbilityActorInfoSet();
}


void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::ClientEffectApplied);
}



void UAuraAbilitySystemComponent::ServerAddAbility_Implementation(const FGameplayTag & AbilityTag , const FGameplayTag& InputTag)
{
	
	if(GetAvatarActor()->HasAuthority())
	{
		UE_LOG(AuraLog , Warning , TEXT("Has Authority"));
	}
	FAbilityInfo AbilityInfo = UAuraBlueprintFunctionLibrary::GetAbilityInfo(GetAvatarActor())->FIndAbilityInfoWithTag(AbilityTag);
	AbilityInfo.InputTag = InputTag;
	AbilityInfo.StateTag = FAuraGameplayTags::Get().Ability_State_Equipped;
	bool IsPass = false;
	for(FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{

		if(Spec.DynamicAbilityTags.HasTagExact(AbilityInfo.InputTag))
		{
			// 当前位置有能力  先卸掉当前位置能力
			Spec.DynamicAbilityTags.RemoveTag(FAuraGameplayTags::Get().Ability_State_Equipped);
			Spec.DynamicAbilityTags.AddTag(FAuraGameplayTags::Get().Ability_State_Eligible);
			Spec.DynamicAbilityTags.RemoveTag(AbilityInfo.InputTag);
			FGameplayTagContainer AbilityContainer;
			GetAbilityTagFromSpec(Spec, AbilityContainer);
			ChangeAbility(AbilityContainer.First());
			/** 被动需要取消激活*/
			if(AbilityInfo.AbilityType.MatchesTag(FAuraGameplayTags::Get().Ability_Passive))
			{
				NetMulticast_PassiveSpellChange(AbilityContainer.First() , false);
			}
			//
			if(IsPass)break;
			IsPass = true;
		}
		if(Spec.Ability.Get()->AbilityTags.HasTagExact(AbilityInfo.AbilityTag))
		{
			// 当前能力在其他位置上 
			if(Spec.DynamicAbilityTags.HasTagExact(FAuraGameplayTags::Get().Ability_State_Equipped))
			{
				Spec.DynamicAbilityTags.AddTag(FAuraGameplayTags::Get().Ability_State_Eligible);
				Spec.DynamicAbilityTags.RemoveTag(FAuraGameplayTags::Get().Ability_State_Equipped);
				FGameplayTagContainer InputContainer;
				GetInputTagFromSpec(Spec, InputContainer);
				Spec.DynamicAbilityTags.RemoveTags(InputContainer);
				DeleteInput(InputContainer.First());
			}
			// 安装能力
			Spec.DynamicAbilityTags.RemoveTag(FAuraGameplayTags::Get().Ability_State_Eligible);
			Spec.DynamicAbilityTags.AddTag(FAuraGameplayTags::Get().Ability_State_Equipped);
			Spec.DynamicAbilityTags.AddTag(AbilityInfo.InputTag);
			if(AbilityInfo.AbilityType.MatchesTag(FAuraGameplayTags::Get().Ability_Passive))
			{
				ActiveAbilityFromSpec(Spec);
				FGameplayTagContainer AbilityContainer;
				GetAbilityTagFromSpec(Spec, AbilityContainer);
				NetMulticast_PassiveSpellChange(AbilityContainer.First() , true);
			}
			if(IsPass)break;
			IsPass = true;
		}
	}
	BroadCastAbilityInfo(AbilityInfo);
	
}


void UAuraAbilitySystemComponent::ClientEffectApplied_Implementation(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& GameplayEffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	 FGameplayTagContainer GameplayContainer;
	GameplayEffectSpec.GetAllAssetTags(GameplayContainer);
	FAppliedAllTags.Broadcast(GameplayContainer);
}



void UAuraAbilitySystemComponent::NetMulticast_PassiveSpellChange_Implementation(const FGameplayTag& SpellTag,const bool IsActive)
{
	
	FOnPassiveSpellChanged.Broadcast(SpellTag, IsActive);
	
}


void UAuraAbilitySystemComponent::ServerDeleteAbility_Implementation(const FGameplayTag& AbilityInput,
	const FGameplayTag& AbilityType)
{
	for(FGameplayAbilitySpec& Spec :GetActivatableAbilities())
	{
		if(Spec.DynamicAbilityTags.HasTagExact(AbilityInput))
		{
			Spec.DynamicAbilityTags.RemoveTag(FAuraGameplayTags::Get().Ability_State_Equipped);
			Spec.DynamicAbilityTags.AddTag(FAuraGameplayTags::Get().Ability_State_Eligible);
			Spec.DynamicAbilityTags.RemoveTag(AbilityInput);
             			
			FGameplayTagContainer AbilityContainer;
			GetAbilityTagFromSpec(Spec, AbilityContainer);
             			
			ChangeAbility(AbilityContainer.First());
			DeleteInput(AbilityInput);
			// 被动取消
			if(AbilityType.MatchesTag(FAuraGameplayTags::Get().Ability_Passive))
			{
				NetMulticast_PassiveSpellChange(AbilityContainer.First() , false);
			}
			return;
		}
	}
}

void UAuraAbilitySystemComponent::GiveAbilitiesArray(TArray<TSubclassOf<UGameplayAbility>>& Abilities)
{
	for (auto& Abi : Abilities)
	{
		FGameplayAbilitySpec SpecA = FGameplayAbilitySpec(Abi, 1);
		if (const UAuraGameplayAbility* AuraAbility = Cast<UAuraGameplayAbility>(SpecA.Ability))
		{
			SpecA.DynamicAbilityTags.AddTag(AuraAbility->ActiveTag);
			SpecA.DynamicAbilityTags.AddTag(FAuraGameplayTags::Get().Ability_State_Equipped);
			GiveAbility(SpecA);
		}
	}

	
}

void UAuraAbilitySystemComponent::GiveBaseAbilitiesArray(TArray<TSubclassOf<UGameplayAbility>>& Abilities)
{
	for (auto& Abi : Abilities)
	{
		FGameplayAbilitySpec SpecA = FGameplayAbilitySpec(Abi, 1);
		GiveAbilityAndActivateOnce(SpecA);
	}
}


/*
 *  被playerController调用  
 */

void UAuraAbilitySystemComponent::PressFunction(FGameplayTag ActionTag)
{
	if (!ActionTag.IsValid())return;
	for (FGameplayAbilitySpec& ASpec : GetActivatableAbilities())
	{

		if (ASpec.DynamicAbilityTags.HasTagExact(ActionTag))
		{
 
			AbilitySpecInputPressed(ASpec);
			if (!ASpec.IsActive())
			{
				TryActivateAbility(ASpec.Handle);
				InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputPressed,ASpec.Handle ,ASpec.ActivationInfo.GetActivationPredictionKey());
				MarkAbilitySpecDirty(ASpec);
			}
		}


	}
}


void UAuraAbilitySystemComponent::ReleaseFunction(FGameplayTag ActionTag)
{
	if (!ActionTag.IsValid())return;
	for (FGameplayAbilitySpec& ASpec : GetActivatableAbilities())
	{
		
		if (ASpec.DynamicAbilityTags.HasTagExact(ActionTag) &&ASpec.IsActive())
		{
			AbilitySpecInputReleased(ASpec);
			InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputReleased,ASpec.Handle ,ASpec.ActivationInfo.GetActivationPredictionKey());
			MarkAbilitySpecDirty(ASpec);
		}
	}
}

void UAuraAbilitySystemComponent::HeldFunction(FGameplayTag ActionTag)
{
	if (!ActionTag.IsValid())return;
}

void UAuraAbilitySystemComponent::AddAttribute(const FGameplayTag& AttributeTag)
{
	if(IPlayerInterface::Execute_GetTalentPoints(GetAvatarActor()) > 0 )
	{
		ServerUpdateAttribute(AttributeTag);
	}
}

void UAuraAbilitySystemComponent::ActiveAbilityFromSpec_Implementation(const FGameplayAbilitySpec& Spec)
{
	TryActivateAbility(Spec.Handle);
	
}


void UAuraAbilitySystemComponent::AddAbilityFromSpec_Implementation(const FGameplayAbilitySpec& Spec)
{
	GiveAbility(Spec);
}

void UAuraAbilitySystemComponent::ServerUpdateSpell_Implementation(const FGameplayTag AbilityTag)
{
	if(FGameplayAbilitySpec * AbilitySpec = FindSpecWithTag(AbilityTag))
	{
		AbilitySpec->Level += 1;
		MarkAbilitySpecDirty(*AbilitySpec);
		IPlayerInterface::Execute_AddSpellPoints(GetAvatarActor() , -1);
	}
	
}



FGameplayAbilitySpec* UAuraAbilitySystemComponent::FindSpecWithTag(const FGameplayTag AbilityTag)
{
	FScopedAbilityListLock ScopedAbilityListLock(*this);
	for(FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		if(Spec.Ability.Get()->AbilityTags.HasTag(AbilityTag))
		{
			return &Spec;
		}
	}
	return nullptr;
}

void UAuraAbilitySystemComponent::GetInputTagFromSpec(const FGameplayAbilitySpec& Spec,
	 FGameplayTagContainer& GameplayTags)
{
	FGameplayTagContainer InputTag;
	InputTag.AddTag(FGameplayTag::RequestGameplayTag(FName("Input")));
	GameplayTags = Spec.DynamicAbilityTags.Filter(InputTag);
}

void UAuraAbilitySystemComponent::GetAbilityTagFromSpec(FGameplayAbilitySpec& Spec,
	FGameplayTagContainer& AbilityContainer)
{
	FGameplayTagContainer AbilityTag;
	AbilityTag.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability")));
	AbilityContainer = Spec.Ability.Get()->AbilityTags.Filter(AbilityTag);
}

void UAuraAbilitySystemComponent::BroadCastAbilityInfo_Implementation(const FAbilityInfo& AbilityInfo)
{
	FOnAbilityInfoChange.Broadcast(AbilityInfo);
}


void UAuraAbilitySystemComponent::ServerUpdateAttribute_Implementation(const FGameplayTag& AttributeTag)
{
	FGameplayEventData Data;
	Data.EventTag = AttributeTag;
	Data.EventMagnitude = 1;
	
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetAvatarActor() , AttributeTag, Data);
	IPlayerInterface::Execute_AddTalentPoints(GetAvatarActor() , -1);
	
	AAuraCharacter * Character =   CastChecked<AAuraCharacter>(GetAvatarActor());
	Character->AddPointsAfterInitAttribute(Character);
}


FGameplayTag UAuraAbilitySystemComponent::GetSpellAbilityTag(const FGameplayAbilitySpec& AbilitySpec)
{
	
	for(auto tag : AbilitySpec.Ability.Get()->AbilityTags)
	{
		if(tag.MatchesAny(FAuraGameplayTags::Get().AbilitySpellTag))
		{
			return tag;
		}
	}
	return FGameplayTag();
}

/**
 * Source Always is this
 */
void UAuraAbilitySystemComponent::ApplyEffectToInit(TSubclassOf<UGameplayEffect>& GE, float level , UObject * Source)
{
	check(GE);
	 FGameplayEffectContextHandle ContextHandle = MakeEffectContext();

	 ContextHandle.AddSourceObject(Source);

	const FGameplayEffectSpecHandle EffectSpecHanlde = MakeOutgoingSpec(GE, level, ContextHandle);

	ApplyGameplayEffectSpecToTarget(*EffectSpecHanlde.Data.Get(), this);
}

void UAuraAbilitySystemComponent::OnRep_ActivateAbilities()
{
	Super::OnRep_ActivateAbilities();
	
	InitAbility = true;
	FAbilityDelegate.ExecuteIfBound();
	if(AAuraCharacter * Character = Cast<AAuraCharacter>(GetAvatarActor()))
	{
		Character->GetPlayerState<AAuraPlayerState>()->InitXpAndLevel();
	}
	
}




void UAuraAbilitySystemComponent::ChangeAbility_Implementation(const FGameplayTag& AbilityTag) 
{
	FOnSpellAbilityChange.Broadcast(AbilityTag);
}

void UAuraAbilitySystemComponent::DeleteInput_Implementation(const FGameplayTag& InputTag) 
{
	FOnSpellInputChange.Broadcast(InputTag);
}





