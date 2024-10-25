// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraPlayerState.h"
#include "AuraAbilitySystemComponent.h"
#include "AuraAttributeSet.h"
#include "Net/UnrealNetwork.h"

AAuraPlayerState::AAuraPlayerState()
{
	NetUpdateFrequency = 100.f; 
	
	AbilityComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystemComponent");
	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
	
}


UAbilitySystemComponent* AAuraPlayerState::GetAbilitySystemComponent() const
{
	return AbilityComponent;
}


void AAuraPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(AAuraPlayerState, Level, COND_None, REPNOTIFY_Always);
}

void AAuraPlayerState::On_RepLevel()
{
	
}


