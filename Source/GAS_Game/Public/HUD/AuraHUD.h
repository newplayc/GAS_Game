// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "WidgetController/AttributeWidgetController.h"
#include "WidgetController/SpellMenuWidgetController.h"
#include "AuraHUD.generated.h"

class UOverlapWidgetController;
class UAuraUserWidget;
class UAuraUserWidgetController;
struct FWidgetContollerParams;

/**
 *  创建 OVerlayController  ,  AttributeController . SpellMenuController .  和 OverlayWidget
 */

UCLASS()
class GAS_GAME_API AAuraHUD : public AHUD
{
	GENERATED_BODY()
public:

	// 获取 OverlayController 没有就创建 并且 调用Controller 的 初始化函数。
	UFUNCTION()
	UOverlapWidgetController* GetOverlayWidgetController(const FWidgetContollerParams& WPC);
	// 同上
	UFUNCTION()
	UAttributeWidgetController* GetAttributeWidgetController(const FWidgetContollerParams& WPC);
	// 同上
	UFUNCTION()
	USpellMenuWidgetController* GetSpellMenuWidgetController(const FWidgetContollerParams& WPC);
	// 初始化 Overlay  初始化组件  Character 调用
	UFUNCTION()
	void IniOverlayWidget(APlayerState* PS, APlayerController* PC, UAbilitySystemComponent* ASC, UAttributeSet* AS);

private:
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeWidgetController>AttributeWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UAttributeWidgetController>AttributeWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<USpellMenuWidgetController>SpellMenuWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<USpellMenuWidgetController>SpellMenuWidgetController;
	
	UPROPERTY()
	TObjectPtr<UAuraUserWidget>OverlayWidget;
	//  主界面类
	UPROPERTY(EditAnywhere )
	TSubclassOf<UAuraUserWidget>OverlayWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UOverlapWidgetController>OverlayWidgetController;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidgetController>OverlayWidgetControllerClass;
};
