// Fill out your copyright notice in the Description page of Project Settings.



#include "AuraHUD.h"
#include "AuraUserWidget.h"
#include "OverlapWidgetController.h"
#include "AuraUserWidgetController.h"
#include "Blueprint/UserWidget.h"




UOverlapWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetContollerParams& WPC)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlapWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetParamas(WPC);
		OverlayWidgetController->BindCallbacksToDependences();
		return OverlayWidgetController;

	}
	return OverlayWidgetController;
}

void AAuraHUD::IniOverlayWidget(APlayerState* PS, APlayerController* PC, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("check OverlayWidgetClass In the BP_AuraHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("check OverlayWidgetControllerClass In the BP_AuraHUD"));

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UAuraUserWidget>(Widget);
	check(OverlayWidget);
	
	FWidgetContollerParams WidgetConteollerParam(PS, PC, ASC, AS);
	UOverlapWidgetController* OWC = GetOverlayWidgetController(WidgetConteollerParam);
	
	check(OWC);
	OverlayWidgetController = OWC;
	OverlayWidget->SetWidgetController(OWC);

	OWC->BroadcastInitailvalues();
	OverlayWidget->AddToViewport();
}
