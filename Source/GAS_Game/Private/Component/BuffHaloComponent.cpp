// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/BuffHaloComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Character/AuraCharacter.h"
#include "GAS/AuraAbilitySystemComponent.h"
UBuffHaloComponent::UBuffHaloComponent(){
	bAutoActivate = false;
}

void UBuffHaloComponent::OnPassiveSpellChanged(const FGameplayTag&SpellTag, bool AOE)
{
	
	if(SpellTag.MatchesTagExact(PassiveTag)){
		if(AOE)
		{
			Activate(true);
		}
		else
		{
			Deactivate();
		}
	}
}

void UBuffHaloComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if(UAuraAbilitySystemComponent * AuraAbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwner())))
	{
		AuraAbilitySystemComponent->FOnPassiveSpellChanged.AddUObject(this,&UBuffHaloComponent::OnPassiveSpellChanged);
	}
	else
	{
		AAuraCharacter * AuraCharacter = Cast<AAuraCharacter>(GetOwner());
		AuraCharacter->OnAbilitySystemComponent.AddLambda([this]()
		{
			UAuraAbilitySystemComponent * AuraAbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwner()));
			AuraAbilitySystemComponent->FOnPassiveSpellChanged.AddUObject(this,&UBuffHaloComponent::OnPassiveSpellChanged);
		});
	}
	



}

