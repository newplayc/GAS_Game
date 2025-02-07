// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AbilitiyInfo.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FAbilityInfo
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly)
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly , BlueprintReadOnly)
	FGameplayTag AbilityTag;

	UPROPERTY(EditDefaultsOnly , BlueprintReadOnly)
	TObjectPtr<UTexture>SpellIcon;

	UPROPERTY(EditDefaultsOnly , BlueprintReadOnly)
	TObjectPtr<UMaterialInstance>BackGround;
	
};


UCLASS()
class GAS_GAME_API UAbilitiyInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	
	
	UPROPERTY(EditDefaultsOnly)
	TArray<FAbilityInfo>AbilityInfos;

	FAbilityInfo FIndAbilityInfoWithTag(const FGameplayTag& AbilityTag)const;
	
};
