// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AuraUserWidgetController.h"
#include "AuraAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AuraUserWidget.h"
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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, Health);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChanged, float, MaxHealth);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChanged, float, Mana);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChanged, float, MaxMana);

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
	FOnHealthChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "DelegateAttribute")
	FOnMaxHealthChanged OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "DelegateAttribute")
	FOnManaChanged OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "DelegateAttribute")
	FOnMaxManaChanged OnMaxManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "DelegateWidgetMessage")
	FOnMessageWidgetRowDelegate FWidgetDelegate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UDataTable> EffectMessageDataTabele;

};

