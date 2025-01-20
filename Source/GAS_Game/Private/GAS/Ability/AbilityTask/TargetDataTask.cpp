// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Ability/AbilityTask/TargetDataTask.h"
#include "AbilitySystemComponent.h"


void UTargetDataTask::Activate()
{

	const bool IsLocalControl = Ability->GetCurrentActorInfo()->IsLocallyControlled();

	/*
	 * TargetData 发送
	 */
	if (IsLocalControl)
	{
		SendTargetData();   
	}
	/*
	 *   
	 */
	else     
	{
		const FGameplayAbilitySpecHandle SpecHandle = GetAbilitySpecHandle();
		const FPredictionKey Pkey = GetActivationPredictionKey();
		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(SpecHandle, Pkey).AddUObject(this,&UTargetDataTask::OnTargetDataCallBack);
		const bool IsSet = AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(SpecHandle, Pkey);
		if(!IsSet)
			SetWaitingOnRemotePlayerData();
	}
}


void UTargetDataTask::SendTargetData()
{
	
    
	FScopedPredictionWindow FScopedPredictionWindow(AbilitySystemComponent.Get());
	FGameplayAbilityTargetData_SingleTargetHit *  SingleHitResult = new FGameplayAbilityTargetData_SingleTargetHit();
	APlayerController* PC = Ability->GetCurrentActorInfo()->PlayerController.Get();
	PC->GetHitResultUnderCursor(ECC_Visibility, false, SingleHitResult->HitResult);
	FGameplayAbilityTargetDataHandle DataHandle;
	DataHandle.Add(SingleHitResult);

	AbilitySystemComponent->ServerSetReplicatedTargetData(
		GetAbilitySpecHandle(),
		GetActivationPredictionKey(), 
		DataHandle, 
		FGameplayTag(),
		AbilitySystemComponent->ScopedPredictionKey);

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		TargetData.Broadcast(DataHandle);
	}

}

/**  服务端 接收到TargetData 的回调函数 */  
void UTargetDataTask::OnTargetDataCallBack(const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag Activation)
{
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		TargetData.Broadcast(DataHandle);
	}
}


UTargetDataTask* UTargetDataTask::CreateTagetData(UGameplayAbility* GameplayAbility)
{
	UTargetDataTask* MyObj = NewAbilityTask<UTargetDataTask>(GameplayAbility);
	return MyObj;	
}
