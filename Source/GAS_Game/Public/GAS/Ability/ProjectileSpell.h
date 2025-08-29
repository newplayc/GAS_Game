// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AuraGameplayAbility.h"
#include "GAS/Ability/AuraGameplayDamageAbility.h"
#include "ProjectileSpell.generated.h"

class AProjectile;
/**
 *  可投射物 技能 基类
 */
UCLASS()
class GAS_GAME_API UProjectileSpell : public UAuraGameplayDamageAbility
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly , BlueprintReadOnly)
	TSubclassOf<AProjectile>ProjectileClass;

	// 内置 生成火球 无需调用
	void CreatFireBolt(FTransform &SpawnTransform, AActor * Target,const FVector& TargetLocation);
	// 调用 生成火球 调整方向 ， 控制 数量 等。 
	UFUNCTION(BlueprintCallable)
	void SpawnFireBolt(const  FVector  & TargetLocation, FGameplayTag SocketTag, AActor * Target, bool bPitchOverride, float PitchOverride) ;

	UPROPERTY(EditDefaultsOnly)
	float SpreadSpeed = 650.f;

	UPROPERTY(EditDefaultsOnly)
	float ProjectileSpread = 90;
	
	UPROPERTY(EditDefaultsOnly)
	FScalableFloat ProjectileNums;

	
};
