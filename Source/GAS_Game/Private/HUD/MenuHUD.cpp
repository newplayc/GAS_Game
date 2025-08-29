// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/MenuHUD.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Widget/LoadScreenMVVM.h"
#include "Widget/LoadWidgetBase.h"

void AMenuHUD::BeginPlay()
{
	Super::BeginPlay();
	
	LoadScreenMVVM = NewObject<ULoadScreenMVVM>(this , LoadScreenMVVMClass);
	LoadScreenMVVM->CreatLoadSlotMVVM();

	APlayerController * Pc = GetWorld()->GetFirstPlayerController();
	Pc->SetShowMouseCursor(true);
	FInputModeGameAndUI InputModeGameAndUI;
	InputModeGameAndUI.SetHideCursorDuringCapture(false);
	InputModeGameAndUI.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	Pc->SetInputMode(InputModeGameAndUI);
	
	LoadWidget = CreateWidget<ULoadWidgetBase>(Pc , LoadScreenWidgetClass);
	LoadWidget->AddToViewport();
	
	LoadWidget->InitializeScreenWidget();
	UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(Pc,LoadWidget);
}
