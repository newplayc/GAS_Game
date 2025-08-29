// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Ability/AuraGameplayDamageAbility.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AuraBlueprintFunctionLibrary.h"


FEffectParams UAuraGameplayDamageAbility::MakeDefaultEffectParams(AActor* TargetActor)
{
	FEffectParams EffectParams;
	EffectParams.DebuffChance = DebuffChance;
	EffectParams.DebuffDamage = DebuffDamage;
	EffectParams.DebuffDuration = DebuffDuration;
	EffectParams.DebuffFrequency = DebuffFrenquency;
	EffectParams.DamageTypeTag = DamageTypeTag;
	EffectParams.AbilityLevel =  GetAbilityLevel();
	EffectParams.DeathImpulseMagnitude = DeathImpulseMagnitude;
	EffectParams.KnockBackMagnitude = KnockBackMagnitude;
	EffectParams.bShouldKnockBack = bShouldKnockBack;
	EffectParams.BaseDamage = DamageValue.GetValueAtLevel(EffectParams.AbilityLevel);
	EffectParams.SourceAbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();
	EffectParams.TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	FGameplayEffectContextHandle EffectContextHandle = EffectParams.SourceAbilitySystemComponent->MakeEffectContext();
	EffectContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	EffectContextHandle.SetAbility(this);
	FGameplayEffectSpecHandle SeSpecHandle = EffectParams.SourceAbilitySystemComponent->MakeOutgoingSpec(DamageEffect , GetAbilityLevel() , EffectContextHandle);
	EffectParams.EffectSpecHandle = SeSpecHandle;
	return EffectParams;
}

void UAuraGameplayDamageAbility::CauseDamage(AActor* Target)
{
	if(UAuraBlueprintFunctionLibrary::IsFriend(Target , GetAvatarActorFromActorInfo()))return;
	if(GetAvatarActorFromActorInfo()->HasAuthority())
	{
		FGameplayEffectSpecHandle SpecHandle =  MakeOutgoingGameplayEffectSpec(DamageEffect, GetAbilityLevel());
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle ,DamageTypeTag, DamageValue.GetValueAtLevel(GetAbilityLevel()));
		GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get() , UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target));
	}
	
}



