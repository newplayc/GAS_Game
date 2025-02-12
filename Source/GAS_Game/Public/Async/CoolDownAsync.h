// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CoolDownAsync.generated.h"


struct FActiveGameplayEffectHandle;
struct FGameplayTag;
class UAbilitySystemComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCoolDown , float , CoolDOwnSecond);
/**
 * 
 */
UCLASS(BlueprintType , meta=(ExposedAsyncProxy))
class GAS_GAME_API UCoolDownAsync : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintAssignable)
	FOnCoolDown CoolDownBegin;

	UPROPERTY(BlueprintAssignable)
	FOnCoolDown CoolDownEnd;
	
	void OnTagChanged(const FGameplayTag GT , int32 Count)const;
	
	void OnEffectApplied(UAbilitySystemComponent* ASC ,  const FGameplayEffectSpec& GEC , FActiveGameplayEffectHandle ActiveGameplayEffectHandle);
	
	UFUNCTION(BlueprintCallable , meta=(BlueprintInternalUseOnly))
	static UCoolDownAsync * CreatCoolDownAsync(UAbilitySystemComponent * ASC , const FGameplayTag CoolDownTag);

	UFUNCTION(BlueprintCallable)
	void EndTask();
protected:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent>ASComp;

	UPROPERTY()
	FGameplayTag CoolTag;
	
};
