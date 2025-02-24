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
 * 
 */

UCLASS()
class GAS_GAME_API AAuraHUD : public AHUD
{
	GENERATED_BODY()
public:




	UFUNCTION()
	UOverlapWidgetController* GetOverlayWidgetController(const FWidgetContollerParams& WPC);


	UFUNCTION()
	UAttributeWidgetController* GetAttributeWidgetController(const FWidgetContollerParams& WPC);

	UFUNCTION()
	USpellMenuWidgetController* GetSpellMenuWidgetController(const FWidgetContollerParams& WPC);

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

	
	UPROPERTY(EditAnywhere )
	TSubclassOf<UAuraUserWidget>OverlayWidgetClass;


	
	UPROPERTY()
	TObjectPtr<UOverlapWidgetController>OverlayWidgetController;


	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidgetController>OverlayWidgetControllerClass;


	

};
