// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "Abilities\GameplayAbilityTargetTypes.h"
#include "TargetDataTask.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTagetData, const FGameplayAbilityTargetDataHandle&, DataHandle);

/**
 * 
 */
UCLASS()
class GAS_GAME_API UTargetDataTask : public UAbilityTask
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintAssignable)
	FOnTagetData TargetData;
	
	virtual void Activate() override;

	void SendTargetData();

	void  OnTargetDataCallBack(const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag Activation);
	// 必备创建接口
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "TargetDataUnderMouse", HidePin = "GameplayAbility", DefaultToSelf = "GameplayAbility", BlueprintInternalUseOnly = "true"))
	static UTargetDataTask* CreateTagetData(UGameplayAbility* GameplayAbility);

};


