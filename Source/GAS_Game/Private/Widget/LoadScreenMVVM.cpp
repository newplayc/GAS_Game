// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/LoadScreenMVVM.h"

#include "AuraGameInstance.h"
#include "Game/AuraGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Widget/LoadSlotMVVM.h"

void ULoadScreenMVVM::CreatLoadSlotMVVM()
{
	check(LoadSlotMVVMClass);
	LoadSlotMvvm_1 = NewObject<ULoadSlotMVVM>(this ,LoadSlotMVVMClass);
	LoadSlotMVVMMap.Add(0 , LoadSlotMvvm_1);
	LoadSlotMvvm_2 = NewObject<ULoadSlotMVVM>(this ,LoadSlotMVVMClass);
	LoadSlotMVVMMap.Add(1 , LoadSlotMvvm_2);
	LoadSlotMvvm_3 = NewObject<ULoadSlotMVVM>(this ,LoadSlotMVVMClass);
	LoadSlotMVVMMap.Add(2 , LoadSlotMvvm_3);
}

// 如果当前 有 选中按钮进入游戏 修改GameInstance 的SlotName 和 PlayerStartTag
void ULoadScreenMVVM::EntryGame()
{
	if(!SelectedSlot.IsValid())return;
	if(AAuraGameModeBase * Gm = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(this)))
	{
		UAuraGameInstance * AuraGameInstance = Cast<UAuraGameInstance>(Gm->GetGameInstance());
		AuraGameInstance->SlotName = SelectedSlot->SlotName;
		AuraGameInstance->PlayerStartTag = SelectedSlot->PlayerStartName;
		
		Gm->EntryGame(SelectedSlot->GetMapName());
	}
	
	
}
// 删除当前选择的 slot
void ULoadScreenMVVM::DeleteGame()
{
	if(!SelectedSlot.IsValid())return;
	if(AAuraGameModeBase * Gm = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(this)))
	{
		Gm->DeleteSlot(SelectedSlot->SlotName , SelectedSlot->SlotIndex);
		SelectedSlot->InitializeMVVVMManul();
		SelectedSlot->BroadcastSlotChangeIndex(0);
		SelectedSlot->OnSlotChanged.Broadcast(-1);
		SelectedSlot = nullptr;
	}
}
// 获取 index 位置的 slotMvvm
ULoadSlotMVVM* ULoadScreenMVVM::GetSlotMVVM(int32 SlotIndex)
{
	return LoadSlotMVVMMap[SlotIndex];
}

// 将Index 位置的slotmvvm 设置为选中 的 Slot
void ULoadScreenMVVM::SlotSelected(int Index)
{
	SelectedSlot =  LoadSlotMVVMMap[Index];
	OnSelectSlot.Broadcast(Index);
}


