// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraAbilitySystemComponent.h"
#include <AuraGameplayAbility.h>



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
	GameplayEffectSpec.GetEffectContext();
	FAppliedAllTags.Broadcast(GameplayContainer);
}


void UAuraAbilitySystemComponent::InitAttribute(UObject * Source)
{
	ApplyEffectToInit(InitalPrimaryEffect, 1 , Source);
	ApplyEffectToInit(InitalSecondaryEffect, 1 , Source);
	ApplyEffectToInit(InitalVitalEffect,1  ,Source);
}


void UAuraAbilitySystemComponent::GiveAbilitiesArray(TArray<TSubclassOf<UGameplayAbility>>& Abilities)
{
	for (auto& Abi : Abilities)
	{

		FGameplayAbilitySpec SpecA = FGameplayAbilitySpec(Abi, 1);
		if (const UAuraGameplayAbility* AuraAbility = Cast<UAuraGameplayAbility>(SpecA.Ability))
		{
			SpecA.DynamicAbilityTags.AddTag(AuraAbility->ActiveTag);
			GiveAbility(SpecA);
		}

	}
}


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





/**
 * Source Always is this
 */
void UAuraAbilitySystemComponent::ApplyEffectToInit(TSubclassOf<UGameplayEffect> GE, float level , UObject * Source)
{
	check(GE);
	 FGameplayEffectContextHandle ContextHandle = MakeEffectContext();

	 ContextHandle.AddSourceObject(Source);

	const FGameplayEffectSpecHandle EffectSpecHanlde = MakeOutgoingSpec(GE, level, ContextHandle);

	ApplyGameplayEffectSpecToTarget(*EffectSpecHanlde.Data.Get(), this);


}
