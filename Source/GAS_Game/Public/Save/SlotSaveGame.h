// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "GameplayTagContainer.h"
#include "SlotSaveGame.generated.h"

USTRUCT()
struct FSaveActor
{
	GENERATED_BODY()

	UPROPERTY()
	FName ActorName;

	UPROPERTY()
	FTransform ActorTransform;

	UPROPERTY()
	TArray<uint8>ActorData;
};
inline bool operator==(const FSaveActor & SaveActor1 , const FSaveActor& SaveActor2)
{
	return SaveActor1.ActorName == SaveActor2.ActorName;
}

USTRUCT()
struct FSaveMap
{
	GENERATED_BODY()

	UPROPERTY()
	FString MapName;

	UPROPERTY()
	TMap<FName , FSaveActor>SaveActors;
	
};

USTRUCT()
struct FPrimaryAttriuteSave
{
	GENERATED_BODY()
	
	UPROPERTY()
	float Strength = 1;

	
	UPROPERTY()
	float Vigor = 1;

	
	UPROPERTY()
	float Intelligence = 1;

	
	UPROPERTY()
	float Resilience = 1;
	
};


USTRUCT()
struct FAttributeSave
{
	GENERATED_BODY()
	
	UPROPERTY()
	int32 Experience = 10;

	UPROPERTY()
	int32 SpellPoints = 0;

	UPROPERTY()
	int32 TalentPoints = 0;
};

USTRUCT()
struct FAbilitySave
{
	GENERATED_BODY()

	UPROPERTY()
	FGameplayTag AbilityTag;
	
	UPROPERTY()
	FGameplayTag InputTag;
	
	UPROPERTY()
	int32  SkillLevel = 1;

	UPROPERTY()
	FGameplayTag StateTag;
};


/**
 * 
 */


UCLASS()
class GAS_GAME_API USlotSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY()
	FString PlayerName;
	
	UPROPERTY()
	FString MapName;

	UPROPERTY()
	int32 Level;

	UPROPERTY()
	FName PlayerStartTagName;

	UPROPERTY()
	TArray<FAbilitySave>AbiltiySaves;

	UPROPERTY()
	FAttributeSave AttributeSave;

	UPROPERTY()
	FPrimaryAttriuteSave PrimaryAttriuteSave;

	UPROPERTY()
	TArray<FSaveMap>MapsWithActor;

	
	bool HasMap(FString Name)
	{
		for(const FSaveMap & SaveMap : MapsWithActor)
		{
			if(SaveMap.MapName == Name)
			{
				return true;
			}
		}
		return false;
	}

	FSaveMap FindSaveMapCopy(const FString &FindMapName)
	{
		for(const FSaveMap & SaveMap : MapsWithActor)
		{
			if(SaveMap.MapName == FindMapName)
			{
				return SaveMap;
			}
		}
		return FSaveMap();
	}

	const FSaveMap * FindSaveMapRef(const FString & FindMapName)
	{
		for( const FSaveMap &SaveMap : MapsWithActor)
		{
			if(SaveMap.MapName == FindMapName)
			{
				return &SaveMap;
			}
		}
		return nullptr;
		
	}

	void SetMap(const FString & FindMapName , const FSaveMap& Map)
	{
		for(FSaveMap & SaveMap : MapsWithActor)
		{
			if(SaveMap.MapName == FindMapName)
			{
				SaveMap = Map;
			}
		}
	}
};
