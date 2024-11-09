// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "AttributeInfo.generated.h"




USTRUCT(BlueprintType)
struct FAttributeInfos
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere , BlueprintReadOnly)
	FGameplayTag GameplayTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName GameplayTagName;

	UPROPERTY(BlueprintReadOnly)
	float Value;

};

/**
 * 
 */


UCLASS()
class GAS_GAME_API UAttributeInfo : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	TArray<FAttributeInfos>AttributeInfoArray;

	const FAttributeInfos FindAttributeInfo(const FGameplayTag& GameplayTag, bool IsLogNotF = false) const;

};
