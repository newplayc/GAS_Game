// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraAssetManager.h"
#include "AuraGameplayTags.h"
#include "AbilitySystemGlobals.h"

const UAuraAssetManager& UAuraAssetManager::Get()
{
	check(GEngine)
	UAuraAssetManager* AssM = Cast<UAuraAssetManager>(GEngine->AssetManager);
	return *AssM;
}

void UAuraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FAuraGameplayTags::AddGameplayTag();
	UAbilitySystemGlobals::Get().InitGlobalData();	
}

