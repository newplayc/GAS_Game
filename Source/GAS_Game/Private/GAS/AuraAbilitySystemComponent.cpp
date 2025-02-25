// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AuraAbilitySystemComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Character/AuraCharacter.h"
#include "GAS/AuraAttributeSet.h"
#include "GAS/Ability/AuraGameplayAbility.h"
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


void UAuraAbilitySystemComponent::ClientEffectApplied_Implementation(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& GameplayEffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	 FGameplayTagContainer GameplayContainer;
	GameplayEffectSpec.GetAllAssetTags(GameplayContainer);
	FAppliedAllTags.Broadcast(GameplayContainer);
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
	//InitAbility = true;
	//FAbilityDelegate.ExecuteIfBound();
	
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
				if (!TryActivateAbility(ASpec.Handle)) {
					GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Red, FString::Printf(TEXT("Faild TO Activate Ability %s"), *ASpec.Ability.GetName()));
				}
			}
		}


	}
}


void UAuraAbilitySystemComponent::ReleaseFunction(FGameplayTag ActionTag)
{
	if (!ActionTag.IsValid())return;
	for (FGameplayAbilitySpec& ASpec : GetActivatableAbilities())
	{
		if (ASpec.DynamicAbilityTags.HasTagExact(ActionTag))
		{
			AbilitySpecInputReleased(ASpec);
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

void UAuraAbilitySystemComponent::AddAbilityFromSpec_Implementation(const FGameplayAbilitySpec& Spec)
{
	GiveAbility(Spec);
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


