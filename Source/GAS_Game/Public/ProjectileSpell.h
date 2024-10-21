// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AuraGameplayAbility.h"
#include "ProjectileSpell.generated.h"


class AProjectile;

/**
 * 
 */
UCLASS()
class GAS_GAME_API UProjectileSpell : public UAuraGameplayAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AProjectile>ProjectileClass;
	

	UFUNCTION(BlueprintCallable)
	void SpawnFireBolt(const FVector  &TargetLocation);
};
