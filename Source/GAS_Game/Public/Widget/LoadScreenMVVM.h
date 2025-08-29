// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "LoadScreenMVVM.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSelectSlot , int32 , SelectIndex);
class ULoadSlotMVVM;



/**
 * 这个类是存档界面的MVVM 总类 管理着 三个 SlotMvvm 以及 选中的slot等 唯一实例保存在MenuHUD
 */
UCLASS()
class GAS_GAME_API ULoadScreenMVVM : public UMVVMViewModelBase
{
	GENERATED_BODY()
public:
	void CreatLoadSlotMVVM();
	
protected:
	UPROPERTY(BlueprintAssignable)
	FOnSelectSlot OnSelectSlot;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ULoadSlotMVVM>LoadSlotMVVMClass;

	UPROPERTY()
	TMap<int32 , ULoadSlotMVVM*>LoadSlotMVVMMap;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ULoadSlotMVVM>LoadSlotMvvm_1;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ULoadSlotMVVM>LoadSlotMvvm_2;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ULoadSlotMVVM>LoadSlotMvvm_3;

public:
	// 
	UFUNCTION(BlueprintCallable)
	void EntryGame();

	UFUNCTION(BlueprintCallable)
	void DeleteGame();

	
	UFUNCTION(BlueprintCallable)
	ULoadSlotMVVM * GetSlotMVVM(int32 SlotIndex);

	UFUNCTION(BlueprintCallable)
	void SlotSelected(int Index);

	UPROPERTY(BlueprintReadOnly)
	FString SlotName_1 = FString("SlotName_1");

	UPROPERTY(BlueprintReadOnly)
	FString SlotName_2 = FString("SlotName_2");

	UPROPERTY(BlueprintReadOnly)
	FString SlotName_3 = FString("SlotName_3");
private:
	TWeakObjectPtr<ULoadSlotMVVM>SelectedSlot;
};
