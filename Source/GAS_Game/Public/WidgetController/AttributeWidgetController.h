// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AuraUserWidgetController.h"
#include "Data/AttributeInfo.h"
#include "AttributeWidgetController.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeDelegateClass,FAttributeInfos,AttriInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTalentChanged , int32 ,TalentPoints);
/**
 *    属性 控制器
 */
UCLASS(Blueprintable , BlueprintType)
class GAS_GAME_API UAttributeWidgetController : public UAuraUserWidgetController
{
	GENERATED_BODY()

public:
	// 属性的 初始化 
	virtual void BroadcastInitailvalues()override;
	// 属性 变化委托绑定
	virtual void BindCallbacksToDependences() override;
	// 属性集合  
	UPROPERTY(EditAnywhere , BlueprintReadOnly)
	TObjectPtr<UAttributeInfo> AttributeInfoData;
	// 蓝图绑定的 委托  通知Ui更新 属性
	UPROPERTY(BlueprintAssignable , Category = "Delegate")
	FAttributeDelegateClass FAttributeDelegate;
	// 通知 UI 更新  天赋点
	UPROPERTY(BlueprintAssignable);
	FOnTalentChanged OnTalentChangedDelegate;
	
	UFUNCTION()
	void OnTalentPointsChanegd(int32 TalentPoints);
	// 添加 天赋点
	UFUNCTION(BlueprintCallable)
	void AddAtttribute(const FGameplayTag& AttributeTag);
};
