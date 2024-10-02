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
public:

	virtual void  HeightLightActor()override ;

	virtual void  UnHeightLightActor()override;

protected:
	

	UPROPERTY(BlueprintReadOnly)
	bool bShouldHeightActor = false;
};
