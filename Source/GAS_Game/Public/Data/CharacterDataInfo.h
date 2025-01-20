// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "Engine/DataAsset.h"
#include "CharacterDataInfo.generated.h"


UENUM(BlueprintType)
enum class ECharacterClass : uint8
{
	Warrior,
	Ranger,
	elementalist
};

USTRUCT(BlueprintType)
struct FCharacterDifDataInfo
{
	GENERATED_BODY()
public:
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect>PrimaryEffect;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UGameplayAbility>>StartingAbilities;
};

/**
 * 在 GameMode中保存实例
 */
UCLASS()
class GAS_GAME_API UCharacterDataInfo : public UDataAsset
{

	
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
	TMap<ECharacterClass , FCharacterDifDataInfo>CharacterInfos;

	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect>SecondaryEffet;

	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect>VitalEffet;

	/**
	 * 通用能力
	 */
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UGameplayAbility>>StartingAbilities;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCurveTable> AttributeCurve;
 
	// UPROPERTY(EditDefaultsOnly)
	// TMap<FGameplayTag, FScalableFloat>DamageTypeData;
	
	FCharacterDifDataInfo GetCharacterDataInfo(ECharacterClass CharaClass) const;

	
};
