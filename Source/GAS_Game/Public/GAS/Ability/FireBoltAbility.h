// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Ability/ProjectileSpell.h"
#include "FireBoltAbility.generated.h"

/**
 * 
 */
UCLASS()
class GAS_GAME_API UFireBoltAbility : public UProjectileSpell
{
	GENERATED_BODY()
public:
	
	
	virtual FString GetLevelDescription(int32 Level) override;
	
	virtual FString GetNextLevelDescription(int32 NowLevel)override;


	
};
