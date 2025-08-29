// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "LoadSlotMVVM.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSlotChanged  , int32 , index);


/**
 * 
 */
UCLASS()
class GAS_GAME_API ULoadSlotMVVM : public UMVVMViewModelBase
{
	GENERATED_BODY()
public:
	// 插槽切换 
	UPROPERTY(BlueprintAssignable)
	FOnSlotChanged OnSlotChanged;

	UFUNCTION(BlueprintCallable)
	void BroadcastSlotChangeIndex(int32 index);
	
	UPROPERTY(BlueprintReadWrite)
	int32 SlotIndex;

	UPROPERTY(BlueprintReadWrite)
	FString SlotName;

	FString GetPlayerName()const;
	void SetPlayerName(FString Name);

	FString GetMapName()const;
	void SetMapName(FString Name);

	int32 GetPlayerLevel()const;
	void SetPlayerLevel(int32 Level);

	void InitializeMVVVMManul();

	
	FName PlayerStartName;
protected:
	UFUNCTION(BlueprintCallable)
	void SaveGameSlot();

	//从硬盘加载存档 切换存档插槽
	UFUNCTION(BlueprintCallable)
	bool LoadSlot();

private:
	
	UPROPERTY(BlueprintReadWrite , FieldNotify , meta=(AllowPrivateAccess = true) , Getter , Setter)
	FString PlayerName;
	
	UPROPERTY(BlueprintReadWrite , FieldNotify , meta=(AllowPrivateAccess = true), Getter , Setter)
	FString MapName = "FirstMap";

	UPROPERTY(BlueprintReadWrite , FieldNotify , meta=(AllowPrivateAccess = true), Getter , Setter)
	int32 PlayerLevel = 1;
	
};
