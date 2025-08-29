// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "Data/InputDataConfig.h"
#include "AuraEnhancedInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class GAS_GAME_API UAuraEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	 
public:
	 template<class UserClass , typename PressFuncType , typename ReleasedFuncType , typename HeldFuncType>
	 void BindAbilityActions(const UInputDataConfig* InputConfig, UserClass* Object, PressFuncType PressFun, ReleasedFuncType ReleasedFun, HeldFuncType HeldFun);
};

template<class UserClass, typename PressFuncType, typename ReleasedFuncType, typename HeldFuncType>
void UAuraEnhancedInputComponent::BindAbilityActions(const UInputDataConfig* InputConfig, UserClass* Object, PressFuncType PressFun, ReleasedFuncType ReleasedFun, HeldFuncType HeldFun)
{
	check(InputConfig);
	for (const FInputData& ID : InputConfig->InputDatas)
	{
		if (ID.InputAction && ID.GameplayTag.IsValid())
		{
			if (HeldFun)
				BindAction(ID.InputAction, ETriggerEvent::Triggered, Object, HeldFun, ID.GameplayTag);
			if (PressFun)
				BindAction(ID.InputAction, ETriggerEvent::Started, Object, PressFun, ID.GameplayTag);
			if (ReleasedFun)
				BindAction(ID.InputAction, ETriggerEvent::Completed, Object, ReleasedFun, ID.GameplayTag);
		}
		
	}
}
