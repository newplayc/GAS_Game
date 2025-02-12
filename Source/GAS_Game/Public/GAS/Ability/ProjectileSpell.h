// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AuraGameplayAbility.h"
#include "GAS/Ability/AuraGameplayDamageAbility.h"
#include "ProjectileSpell.generated.h"

class AProjectile;
/**
 * 
 */
UCLASS()
class GAS_GAME_API UProjectileSpell : public UAuraGameplayDamageAbility
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly , BlueprintReadOnly)
	TSubclassOf<AProjectile>ProjectileClass;
	

	UFUNCTION(BlueprintCallable)
	void SpawnFireBolt(const  FVector  & TargetLocation , FGameplayTag SocketTag) ;
	
};
