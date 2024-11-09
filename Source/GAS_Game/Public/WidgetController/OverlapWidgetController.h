// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AuraUserWidgetController.h"
#include "AbilitySystemComponent.h"
#include "Widget/AuraUserWidget.h"
#include "OverlapWidgetController.generated.h"




USTRUCT(BlueprintType)
struct FUIWidgetRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
	FGameplayTag MessageTag = FGameplayTag();

	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
	FText Message = FText();

	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
	TSubclassOf<UAuraUserWidget>MessageWidget;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
	UTexture2D* Image;


};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChanged, float, NewValue);


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMessageWidgetRowDelegate, FUIWidgetRow , WidgetRow);




/**
 * 
 */
UCLASS(BlueprintType , Blueprintable)
class GAS_GAME_API UOverlapWidgetController : public UAuraUserWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitailvalues()override;

	virtual void BindCallbacksToDependences() override;

	UPROPERTY(BlueprintAssignable , Category = "DelegateAttribute")
	FOnAttributeChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "DelegateAttribute")
	FOnAttributeChanged OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "DelegateAttribute")
	FOnAttributeChanged OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "DelegateAttribute")
	FOnAttributeChanged OnMaxManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "DelegateWidgetMessage")
	FOnMessageWidgetRowDelegate FWidgetDelegate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UDataTable> EffectMessageDataTable;


};

