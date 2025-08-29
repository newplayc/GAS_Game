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
	 *   再服务端 
	 */
	else     
	{
		const FGameplayAbilitySpecHandle SpecHandle = GetAbilitySpecHandle();
		const FPredictionKey Pkey = GetActivationPredictionKey();
		// 添加回调  服务端收到了 TargetData 信息
		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(SpecHandle, Pkey).AddUObject(this,&UTargetDataTask::OnTargetDataCallBack);

		//检测是否有可用的目标信息  可以理解为服务端 是否收到了 客户端发送来的信息。
		const bool IsSet = AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(SpecHandle, Pkey);
		// 没有 收到信息 就 等待 或者 取消这个能力。
		if(!IsSet)  
			SetWaitingOnRemotePlayerData();
	}
}


void UTargetDataTask::SendTargetData()
{
	
	FScopedPredictionWindow FScopedPredictionWindow(AbilitySystemComponent.Get());

	// 创建 想要发送的信息。
	FGameplayAbilityTargetData_SingleTargetHit *  SingleHitResult = new FGameplayAbilityTargetData_SingleTargetHit();
	
	APlayerController* PC = Ability->GetCurrentActorInfo()->PlayerController.Get();
	PC->GetHitResultUnderCursor(ECC_Visibility, false, SingleHitResult->HitResult);
	
	FGameplayAbilityTargetDataHandle DataHandle;
	
	DataHandle.Add(SingleHitResult);
    // 发送信息。
	AbilitySystemComponent->ServerSetReplicatedTargetData(
		GetAbilitySpecHandle(),
		GetActivationPredictionKey(), 
		DataHandle, 
		FGameplayTag(),
		AbilitySystemComponent->ScopedPredictionKey);
	// 判断 是否需要 广播 收到的 信息 确保能力 再 激活状态 这句话 发生在 客户端
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		TargetData.Broadcast(DataHandle);
	}

}

/**  服务端 接收到TargetData 的回调函数 */  
void UTargetDataTask::OnTargetDataCallBack(const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag Activation)
{
	// 收到 了 Target Data 信息后 使用掉 这次 信息 
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());
	// 再 服务端 广播
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
