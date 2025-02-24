// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/AbilitiyInfo.h"
#include "WidgetController/AuraUserWidgetController.h"
#include "SpellMenuWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSpellChange , int32 ,NewValue);
/**
 * 
 */
UCLASS(BlueprintType , Blueprintable)
class GAS_GAME_API USpellMenuWidgetController : public UAuraUserWidgetController
{
	GENERATED_BODY()

public:
	virtual void BindCallbacksToDependences() override;
	
	UPROPERTY(BlueprintAssignable)
	FSpellChange OnSpellChange;
protected:
	UFUNCTION()
	void OnSpellPointChange(int32 SpellPoints);


};
