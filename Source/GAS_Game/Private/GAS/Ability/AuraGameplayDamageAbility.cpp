// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Ability/AuraGameplayDamageAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AuraBlueprintFunctionLibrary.h"
#include "RenderGraphBuilder.h"

void UAuraGameplayDamageAbility::CauseDamage(AActor* Target)
{
	if(UAuraBlueprintFunctionLibrary::IsFriend(Target , GetAvatarActorFromActorInfo()))return;
	if(GetAvatarActorFromActorInfo()->HasAuthority())
	{
		FGameplayEffectSpecHandle SpecHandle =  MakeOutgoingGameplayEffectSpec(DamageEffect, GetAbilityLevel());
		UAbilitySystemComponent * GAS =  UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);
		for(auto Dam : DamageTypes)
		{
			
			UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle , Dam.Key, Dam.Value.GetValueAtLevel(GetAbilityLevel()));
		}
		GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get() , UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target));
	}
}
