// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoadWidgetBase.generated.h"

class ULoadScreenMVVM;

/**
 *   存档界面 的 基类 
 */
UCLASS()
class GAS_GAME_API ULoadWidgetBase : public UUserWidget
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void InitializeScreenWidget();
	
};
