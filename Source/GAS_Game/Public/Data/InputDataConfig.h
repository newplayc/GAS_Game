// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InputAction.h"
#include "Engine/DataAsset.h"
#include "InputDataConfig.generated.h"


USTRUCT(BlueprintType)
struct FInputData
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	 FGameplayTag GameplayTag;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction>InputAction;

};


/**
 *  
 */
UCLASS()
class GAS_GAME_API UInputDataConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	TArray<FInputData>InputDatas;

	const UInputAction* FindInputActionForTag(const FGameplayTag& GT, bool bLogNF) const;
};
