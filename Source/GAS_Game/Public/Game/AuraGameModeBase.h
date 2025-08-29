// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/CharacterDataInfo.h"
#include "GameFramework/GameModeBase.h"
#include "AuraGameModeBase.generated.h"

class AAuraEnemy;
class USlotSaveGame;
class ULoadSlotMVVM;
class USaveGame;
/**
 * 
 */
UCLASS()
class GAS_GAME_API AAuraGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:

	
	// 选择 出生点 
	AActor* ChoosePlayerStart_Implementation(AController* Player);
	
	virtual void BeginPlay() override;

	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCharacterDataInfo>CharacterDataInfo;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USaveGame>SlotSaveGameClass;
	
	void SaveMapActors(UWorld  * Level, FString SlotName , int32 SlotIndex) const;
	void LoadMapActors(UWorld  * Level, FString SlotName , int32 SlotIndex) const;


	static void SaveGame(USlotSaveGame * SlotSaveGame , FString SlotName , int32 SlotIndex);
	void SaveSlotGame(const ULoadSlotMVVM * SlotMVVM)const ;
	USlotSaveGame* LoadSlot(const FString& SlotName , const int32  Index)const;
	void EntryGame(FString WorldName);
	
	void DeleteSlot(const FString& SlotName , const int32 Index)const;
	FString GetFirstMapName(){return FirstName;}
	// 保存 游戏的所有地图 
	UPROPERTY(EditDefaultsOnly)
	TMap<FString, TSoftObjectPtr<UWorld>>WorldMap;
	
	UPROPERTY(EditDefaultsOnly)
	FName PlayerDefaultStartTag;

	
	
	UFUNCTION(BlueprintCallable)
	void SpawnEnemy();

	bool GetReachablePoint(FVector & ResultLocation) const;
	UFUNCTION()
	void OnEnemyDie();
	
protected:
	UPROPERTY(EditDefaultsOnly)
	FString FirstName = "DefaultMapName";

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld>FirstMap;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<AAuraEnemy>>Enemyclass;
	
	UPROPERTY(EditDefaultsOnly , BlueprintReadOnly)
	int32 MaxNumberOfEnemies;
	
	int32 NowEnemies = 0;

	UPROPERTY(EditDefaultsOnly , BlueprintReadOnly)
	float EnemyRadious = 500.f;
};
