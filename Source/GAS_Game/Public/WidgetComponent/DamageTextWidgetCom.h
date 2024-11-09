// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "DamageTextWidgetCom.generated.h"

/**
 * 
 */
UCLASS()
class GAS_GAME_API UDamageTextWidgetCom : public UWidgetComponent
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintImplementableEvent ,BlueprintCallable)
	void SetDamageText(const float damage ,bool IsBlock , bool IsDamage);



	
};
