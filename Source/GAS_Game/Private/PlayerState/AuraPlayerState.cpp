// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerState/AuraPlayerState.h"

#include "AuraBlueprintFunctionLibrary.h"
#include "Game/AuraGameModeBase.h"
#include "GAS/AuraAbilitySystemComponent.h"
#include "GAS/AuraAttributeSet.h"
#include "Kismet/GameplayStatics.h"
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
	DOREPLIFETIME_CONDITION_NOTIFY(AAuraPlayerState, Experience, COND_None, REPNOTIFY_Always);
}

void AAuraPlayerState::SetExp(float InExp)
{
	Experience = InExp;
}

void AAuraPlayerState::SetLevel(int InLevel)
{
	Level = InLevel;
}

void AAuraPlayerState::AddExp(float InExp)
{
	Experience+=InExp;
	AAuraGameModeBase * Gmb = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(this));
	const int ChLevel = Gmb->CharacterDataInfo.Get()->LevelInfos.Get()->FindExpForLevel(Experience);
	if(ChLevel !=Level)
	{
		SetLevel(ChLevel);
	}
	
	float per = UAuraBlueprintFunctionLibrary::GetExpPercent(this,Level , Experience);
	OnExpChangePs.Execute(per);
}

void AAuraPlayerState::AddLevel(int InLevel)
{
	Level +=InLevel;
}

void AAuraPlayerState::InitXpAndLevel()
{

	float per = UAuraBlueprintFunctionLibrary::GetExpPercent(this,Level , Experience);
	OnExpChangePs.Execute(per);
}

void AAuraPlayerState::On_RepLevel(){}
void AAuraPlayerState::On_RepExp(){}


