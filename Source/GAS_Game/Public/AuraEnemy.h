// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AuraCharacterBase.h"
#include "EnemyInterface.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class GAS_GAME_API AAuraEnemy : public AAuraCharacterBase , public IEnemyInterface
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay()override;
public:
	AAuraEnemy();

	virtual void  HeightLightActor()override ;

	virtual void  UnHeightLightActor()override;

	virtual void IniAbilityInfo() override;
};
