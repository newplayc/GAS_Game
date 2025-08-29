// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/LoadSlotMVVM.h"

#include "AuraGameInstance.h"
#include "Game/AuraGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Save/SlotSaveGame.h"

void ULoadSlotMVVM::BroadcastSlotChangeIndex(int32 index)
{
	OnSlotChanged.Broadcast(index);
}

FString ULoadSlotMVVM::GetPlayerName() const
{
	return PlayerName;
}

void ULoadSlotMVVM::SetPlayerName(FString Name)
{
	UE_MVVM_SET_PROPERTY_VALUE(PlayerName , Name);
}

FString ULoadSlotMVVM::GetMapName() const
{
	return MapName;
}

void ULoadSlotMVVM::SetMapName(FString Name)
{
	UE_MVVM_SET_PROPERTY_VALUE(MapName,Name);
}

int32 ULoadSlotMVVM::GetPlayerLevel() const
{
	return PlayerLevel;
}

void ULoadSlotMVVM::SetPlayerLevel(int32 Level)
{
	UE_MVVM_SET_PROPERTY_VALUE(PlayerLevel , Level);
}

void ULoadSlotMVVM::InitializeMVVVMManul()
{
	SetMapName("");
	SetPlayerLevel(1);
	SetPlayerName("");
}
//  创建角色 输入名字之后创建存档  
void ULoadSlotMVVM::SaveGameSlot() 
{

	// 这个 GM 为 MenuGameMode 记录着 角色出生的首张地图和 角色出生地
	AAuraGameModeBase * Gm = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(this));
	bool is = Gm->HasAuthority();
	
	SetMapName(Gm->GetFirstMapName());
	PlayerStartName = Gm->PlayerDefaultStartTag;
	Gm->SaveSlotGame(this);
}

bool ULoadSlotMVVM::LoadSlot()
{
	AAuraGameModeBase * Gm = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(this));
	if(USlotSaveGame* SlotSaveGame=  Gm->LoadSlot(SlotName , SlotIndex))
	{
		SetPlayerLevel(SlotSaveGame->Level);
		SetMapName(SlotSaveGame->MapName);
		SetPlayerName(SlotSaveGame->PlayerName);
		PlayerStartName = SlotSaveGame->PlayerStartTagName;
		return true;
	}
	return false;
}
