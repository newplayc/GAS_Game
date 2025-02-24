// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AuraUserWidgetController.h"
#include "Data/AttributeInfo.h"
#include "AttributeWidgetController.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeDelegateClass,FAttributeInfos,AttriInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTalentChanged , int32 ,TalentPoints);
/**
 * 
 */
UCLASS(Blueprintable , BlueprintType)
class GAS_GAME_API UAttributeWidgetController : public UAuraUserWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitailvalues()override;
	
	virtual void BindCallbacksToDependences() override;
	
	UPROPERTY(EditAnywhere , BlueprintReadOnly)
	TObjectPtr<UAttributeInfo> AttributeInfoData;
	
	UPROPERTY(BlueprintAssignable , Category = "Delegate")
	FAttributeDelegateClass FAttributeDelegate;

	UPROPERTY(BlueprintAssignable);
	FOnTalentChanged OnTalentChangedDelegate;
	
	UFUNCTION()
	void OnTalentPointsChanegd(int32 TalentPoints);

	UFUNCTION(BlueprintCallable)
	void AddAtttribute(const FGameplayTag& AttributeTag);
};
