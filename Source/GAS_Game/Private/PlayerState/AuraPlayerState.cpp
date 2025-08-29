// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerState/AuraPlayerState.h"
#include "Character/AuraCharacter.h"
#include "Data/LevelInfo.h"
#include "GAS/AuraAbilitySystemComponent.h"
#include "GAS/AuraAttributeSet.h"
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
	DOREPLIFETIME(AAuraPlayerState , Experience);
	DOREPLIFETIME(AAuraPlayerState , Level);
	DOREPLIFETIME(AAuraPlayerState , SpellPoints);
	DOREPLIFETIME(AAuraPlayerState , TalentPoints);
}

void AAuraPlayerState::SetExp(int32 InExp)
{
	Experience = InExp;
	const int ChLevel = LevelInfos->FindExpForLevel(Experience);
	if(ChLevel !=Level)
	{
		SetLevel(ChLevel);
	}
	OnExpChangePs.Broadcast(Experience);
}

void AAuraPlayerState::SetLevel(int32 InLevel)
{

	int32 LevelDis = InLevel - Level;
	while(LevelDis-- > 0 )
	{
		Level+=1;
		Level_Up();
	}
	OnLevelChangePs.Broadcast(Level);
}

void AAuraPlayerState::AddExp(int32 InExp)
{

	Experience+=InExp;
	const int ChLevel = LevelInfos->FindExpForLevel(Experience);
	if(ChLevel !=Level)
	{
		SetLevel(ChLevel);
	}
	OnExpChangePs.Broadcast(Experience);
}

void AAuraPlayerState::AddLevel( int32 InLevel)
{
	while(InLevel-- > 0 )
	{
		Level+=1;
		Level_Up();
	}
	OnLevelChangePs.Broadcast(Level);
}

void AAuraPlayerState::AddSpellPoints(int32 InSpellPoints)
{
	SpellPoints +=InSpellPoints;
	OnSpellPointsChangePs.Broadcast(SpellPoints);
}

void AAuraPlayerState::SetSpellPoints(int32 InSpellPoints)
{
	SpellPoints = InSpellPoints;
	OnSpellPointsChangePs.Broadcast(SpellPoints);
}

void AAuraPlayerState::AddTalentPoints(int32 InTalentPoints)
{
	TalentPoints += InTalentPoints;
	OnTalentPointsChnagePs.Broadcast(TalentPoints);
}

void AAuraPlayerState::SetTalentPoints(int32 InTalentsPoints)
{
	TalentPoints = InTalentsPoints;
	OnTalentPointsChnagePs.Broadcast(TalentPoints);
}


void AAuraPlayerState::InitXpAndLevel()const
 {
 	OnExpChangePs.Broadcast(Experience);
 	OnLevelChangePs.Broadcast(Level);
 	OnTalentPointsChnagePs.Broadcast(TalentPoints);
 	OnSpellPointsChangePs.Broadcast(SpellPoints);
 }



void AAuraPlayerState::Level_Up()
 {
	
	int32 SpellAward  = LevelInfos->GetAwardSpellPoints(Level);
	AddSpellPoints(SpellAward);
	int32 TalentAward = LevelInfos->GetAwardTalentPoints(Level);
	AddTalentPoints(TalentAward);

	Cast<AAuraCharacter>(GetPawn())->Level_up();
	
 }

void AAuraPlayerState::On_RepLevel()const
{
	OnLevelChangePs.Broadcast(Level);
}

void AAuraPlayerState::On_RepExp()const
{
	OnExpChangePs.Broadcast(Experience);
}

void AAuraPlayerState::On_RepSpellPoints() const
{
	OnSpellPointsChangePs.Broadcast(SpellPoints);
}

void AAuraPlayerState::On_RepTalentPoints() const
{
	OnTalentPointsChnagePs.Broadcast(TalentPoints);
}

float AAuraPlayerState::GetExpPercent(int32 NowExp)
{
	int32 InLevel = LevelInfos->FindExpForLevel(NowExp);
	if(InLevel>= LevelInfos->LevelInfos.Num()-1)return 1;
	float Percent = (NowExp - LevelInfos->LevelInfos[InLevel].NeedExp) / (LevelInfos->LevelInfos[InLevel+1].NeedExp - NowExp);
	return Percent;
}


