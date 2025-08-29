// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MenuHUD.generated.h"

class ULoadWidgetBase;
class ULoadScreenMVVM;

/**
 *  创建 存档界面 和LoadScreenMvvm
 */
UCLASS()
class GAS_GAME_API AMenuHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ULoadScreenMVVM>LoadScreenMVVM;

	
	UPROPERTY()
	TObjectPtr<ULoadWidgetBase>LoadWidget;

protected:
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ULoadScreenMVVM>LoadScreenMVVMClass;
	// 创建 存档界面 
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget>LoadScreenWidgetClass;
	
	virtual void BeginPlay() override;
};
