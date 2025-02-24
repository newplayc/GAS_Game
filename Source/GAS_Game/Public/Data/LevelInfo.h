// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LevelInfo.generated.h"


USTRUCT(BlueprintType)
struct FChangeLeveInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	int32 Level;

	UPROPERTY(EditDefaultsOnly)
	int32 AwardSpellPoints;

	UPROPERTY(EditDefaultsOnly)
	int32 AwardTalentPoints;
	
	UPROPERTY(EditDefaultsOnly)
	float NeedExp;



	
	
};
/**
 * 
 */

UCLASS()
class GAS_GAME_API ULevelInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	// [0] Is empty  [1] 1 Level Need Exp
	UPROPERTY(EditDefaultsOnly)
	TArray<FChangeLeveInfo>LevelInfos;

	UFUNCTION(BlueprintCallable)
	int32 FindExpForLevel(float NowExp);

	UFUNCTION(BlueprintCallable)
	int32 GetAwardSpellPoints(int32 Level);

	UFUNCTION(BlueprintCallable)
	int32 GetAwardTalentPoints(int32 Level);
	
};
