// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/AuraGameModeBase.h"

#include <SceneExport.h>

#include "AuraGameInstance.h"
#include "EngineUtils.h"
#include "NavigationSystem.h"
#include "Character/AuraEnemy.h"
#include "GameFramework/PlayerStart.h"
#include "GAS_Game/AuraLog.h"
#include "Interface/SaveActorInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Save/SlotSaveGame.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"
#include "Widget/LoadSlotMVVM.h"


AActor* AAuraGameModeBase::ChoosePlayerStart_Implementation(AController* Player)
{
	TArray<AActor*>PlayerStarts;
	UGameplayStatics::GetAllActorsOfClass(this , APlayerStart::StaticClass() ,PlayerStarts);
	if(PlayerStarts.IsEmpty())return nullptr;
	UAuraGameInstance * AGI = Cast<UAuraGameInstance>(GetGameInstance());
	if(!AGI || !AGI->PlayerStartTag.IsValid())return PlayerStarts[0];
	for(auto OrActor : PlayerStarts)
	{
		APlayerStart * PlayerStart = Cast<APlayerStart>(OrActor);
		if(PlayerStart->PlayerStartTag == AGI->PlayerStartTag)
		{
			return PlayerStart;
		}
	}
	return PlayerStarts[0];
}


void AAuraGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	WorldMap.Add(FirstName , FirstMap);
}

// 把当前地图 Actor 序列化
void AAuraGameModeBase::SaveMapActors(UWorld  * Level , FString SlotName , int32 SlotIndex) const
{
	if(USlotSaveGame  * SlotSaveGame = LoadSlot(SlotName , SlotIndex))
	{
		FString GetMapName = Level->GetMapName();
		GetMapName.RemoveFromStart(Level->StreamingLevelsPrefix);
		FSaveMap SaveMap;
		SaveMap.MapName = GetMapName;
		for(FActorIterator It(Level) ; It ; ++It)
		{
			if(It->Implements<USaveActorInterface>())
			{
				FSaveActor SaveActor;
				SaveActor.ActorName = It->GetFName();
				SaveActor.ActorTransform = It->GetTransform(); 
				FMemoryWriter MemoryWriter(SaveActor.ActorData , true);
				FObjectAndNameAsStringProxyArchive Archive(MemoryWriter ,true);
				It->Serialize(Archive);
				SaveMap.SaveActors.Add(SaveActor.ActorName , SaveActor);
			}
		}
		if(SlotSaveGame->HasMap(GetMapName))
		{
			SlotSaveGame->SetMap(GetMapName , SaveMap);
		}
		else
		{
			SlotSaveGame->MapsWithActor.Add(SaveMap);
		}
		SaveGame(SlotSaveGame , SlotName , SlotIndex);
	}
}

// 在插槽加载 被存储的Actor
void AAuraGameModeBase::LoadMapActors(UWorld* Level, FString SlotName, int32 SlotIndex) const
{
	if(USlotSaveGame  * SlotSaveGame = LoadSlot(SlotName , SlotIndex))
	{
		// 移除关卡附加的前缀名
		FString GetMapName = Level->GetMapName();
		GetMapName.RemoveFromStart(Level->StreamingLevelsPrefix);
		// 从Slot寻找map
		if(SlotSaveGame->HasMap(GetMapName))
		{
			const FSaveMap* SaveMap = SlotSaveGame->FindSaveMapRef(GetMapName);
			// 使用 FActorIterator遍历 UWorld 的Actor
			for(FActorIterator It(Level) ; It ; ++It)
			{
				if(It->Implements<USaveActorInterface>())
				if(const FSaveActor* SaveActor = SaveMap->SaveActors.Find(It->GetFName()))
				{
					It->SetActorTransform(SaveActor->ActorTransform);
					FMemoryReader MemoryReader(SaveActor->ActorData);
					FObjectAndNameAsStringProxyArchive Archive(MemoryReader ,true);
					It->Serialize(Archive);
				}
			}
		}
	}
}


void AAuraGameModeBase::SaveGame(USlotSaveGame* SlotSaveGame, FString SlotName, int32 SlotIndex)
{
	if(UGameplayStatics::DoesSaveGameExist(SlotName ,SlotIndex))
	{
		UGameplayStatics::DeleteGameInSlot(SlotName , SlotIndex);
	}
	UGameplayStatics::SaveGameToSlot(SlotSaveGame ,SlotName , SlotIndex);
}


// 在UI 界面 创建角色 输入名字之后根据MVVM创建存档
void AAuraGameModeBase::SaveSlotGame(const ULoadSlotMVVM * SlotMvvm)const
{
	
	if(UGameplayStatics::DoesSaveGameExist(SlotMvvm->SlotName ,SlotMvvm->SlotIndex))
	{
		UGameplayStatics::DeleteGameInSlot(SlotMvvm->SlotName , SlotMvvm->SlotIndex);
	}
	USaveGame * SaveGame = UGameplayStatics::CreateSaveGameObject(SlotSaveGameClass);
	USlotSaveGame * SlotSaveGame = Cast<USlotSaveGame>(SaveGame);

	
	SlotSaveGame->PlayerName = SlotMvvm->GetPlayerName();
	SlotSaveGame->MapName = SlotMvvm->GetMapName();
	SlotSaveGame->Level = SlotMvvm->GetPlayerLevel();
	SlotSaveGame->PlayerStartTagName = SlotMvvm->PlayerStartName;
	
	UGameplayStatics::SaveGameToSlot(SlotSaveGame ,SlotMvvm->SlotName , SlotMvvm->SlotIndex);
}


USlotSaveGame* AAuraGameModeBase::LoadSlot(const FString& SlotName , const int32  Index)const
{
	USaveGame * SaveGame = UGameplayStatics::LoadGameFromSlot(SlotName , Index);
	return Cast<USlotSaveGame>(SaveGame);
}

void AAuraGameModeBase::EntryGame(FString WorldName)
{
	UGameplayStatics::OpenLevelBySoftObjectPtr(this , WorldMap.FindChecked(WorldName));
		
}


void AAuraGameModeBase::DeleteSlot(const FString& SlotName, const int32 Index) const
{
	if(UGameplayStatics::DoesSaveGameExist(SlotName ,Index )){
		UGameplayStatics::DeleteGameInSlot(SlotName , Index);	
	}
}

void AAuraGameModeBase::SpawnEnemy()
{
	checkf(!Enemyclass.IsEmpty() , TEXT("GameMode EnemyClass Is empty"));
	UWorld* World = GetWorld();
	if (World==nullptr)
	{
		UE_LOG(AuraLog , Warning , TEXT("No World When Spawn Enemy"));
		return;
	}
	while (NowEnemies < MaxNumberOfEnemies){
		int randomIndex = UKismetMathLibrary::RandomInteger( Enemyclass.Num());
		FVector SpawnLocation;
		if (GetReachablePoint(SpawnLocation))
		{
			AAuraEnemy * Enemy =  World->SpawnActor<AAuraEnemy>(Enemyclass[randomIndex] , SpawnLocation , FRotator(0.0f) );
			if (Enemy)
			{
				Enemy->AutoPossessAI = EAutoPossessAI::Spawned;
				Enemy->OnEnemyDeath.BindDynamic(this, &AAuraGameModeBase::OnEnemyDie);
				NowEnemies++;
			}
			else
			{
				UE_LOG(AuraLog , Warning , TEXT("Spawn Enemy fail!!!"));
				return;
			}
		}
		else
		{
			UE_LOG(AuraLog ,Warning , TEXT("No Location To Spawn Enemy "));
			return;
		}
	}
}


bool AAuraGameModeBase::GetReachablePoint(FVector & ResultLocation) const
{


	if (UWorld * World = GetWorld())
	{
		FVector PlayerLocation = UGameplayStatics::GetPlayerCharacter(this ,0)->GetActorLocation();
		UNavigationSystemV1 * NavigationSystemV1 = UNavigationSystemV1::GetNavigationSystem(GetWorld());
		FNavLocation NavLocation;
		if (NavigationSystemV1->GetRandomReachablePointInRadius(PlayerLocation , EnemyRadious , NavLocation))
		{
			ResultLocation = NavLocation;
			return true;
		}
	}
	return false;
}


void AAuraGameModeBase::OnEnemyDie()
{
	NowEnemies--;
	SpawnEnemy();
}


