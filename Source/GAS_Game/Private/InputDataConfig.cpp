// Fill out your copyright notice in the Description page of Project Settings.


#include "InputDataConfig.h"

const UInputAction* UInputDataConfig::FindInputActionForTag(const FGameplayTag& GT, bool bLogNF) const
{
	for (const FInputData& ID : InputDatas)
	{
		if (ID.GameplayTag.MatchesTagExact(GT) && ID.InputAction) {
			return ID.InputAction;
		}
	}

	if (bLogNF)
	{
		UE_LOG(LogTemp, Error, TEXT("Cant Find InputAction"));
		

	}
	return nullptr;
}
