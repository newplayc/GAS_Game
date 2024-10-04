// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UOverlapWidgetController;
class UAuraUserWidget;
class UAuraUserWidgetController;
struct FWidgetContollerParams;

/**
 * 
 */

UCLASS()
class GAS_GAME_API AAuraHUD : public AHUD
{
	GENERATED_BODY()
public:
	UPROPERTY()
	TObjectPtr<UAuraUserWidget>OverlayWidget;

	UPROPERTY()
	TObjectPtr<UOverlapWidgetController>OverlayWidgetController;

	UFUNCTION()
	UOverlapWidgetController* GetOverlayWidgetController(const FWidgetContollerParams& WPC);

	UFUNCTION()
	void IniOverlayWidget(APlayerState* PS, APlayerController* PC, UAbilitySystemComponent* ASC, UAttributeSet* AS);




private:

	UPROPERTY(EditAnywhere )
	TSubclassOf<UAuraUserWidget>OverlayWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidgetController>OverlayWidgetControllerClass;

};
