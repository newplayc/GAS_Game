// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "OverlapWidgetController.h"
#include "AttributeWidgetController.h"
#include "AuraBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class GAS_GAME_API UAuraBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
		

public:

	UFUNCTION(BlueprintPure , BlueprintCallable)
	static UOverlapWidgetController* GetOverlayWidgetController(UObject * WorldContext);


	UFUNCTION(BlueprintPure, BlueprintCallable)
	static UAttributeWidgetController* GetAttributeWidgetController(UObject* WorldContext);
};
