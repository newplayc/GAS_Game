// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <AuraUserWidgetController.h>
#include "AuraUserWidget.generated.h"



/**
 * 
 * 
 * 
 */
UCLASS()
class GAS_GAME_API UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
	
public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

	UPROPERTY(BlueprintReadOnly)
	UObject* WidgetController;

	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
	
};
