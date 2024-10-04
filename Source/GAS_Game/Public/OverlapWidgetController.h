// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AuraUserWidgetController.h"
#include "AuraAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "OverlapWidgetController.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, Health);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChanged, float, MaxHealth);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChanged, float, Mana);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChanged, float, MaxMana);
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

protected:

	void OnHealthChangeCallback(const FOnAttributeChangeData& Data) const;

	void OnMaxHealthChangeCallback(const FOnAttributeChangeData& Data) const;

	void OnManaChangeCallback(const FOnAttributeChangeData& Data) const;

	void OnMaxManaChangeCallback(const FOnAttributeChangeData& Data) const;
};
