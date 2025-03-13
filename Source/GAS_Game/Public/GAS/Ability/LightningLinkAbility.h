// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Ability/AuraGameplayDamageAbility.h"
#include "LightningLinkAbility.generated.h"

/**
 * 
 */

UCLASS()
class GAS_GAME_API ULightningLinkAbility : public UAuraGameplayDamageAbility
{
	GENERATED_BODY()


public:
	
protected:
	UPROPERTY(EditDefaultsOnly)
	float LightningTraceRadius = 15.f;

	UPROPERTY(EditDefaultsOnly , BlueprintReadOnly)
	int32 LinkNums = 1;

	UPROPERTY(EditDefaultsOnly , BlueprintReadOnly)
	float LinkNearEnemyRadius = 300.f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	float DamageFrequency = 1.f;
	
	UFUNCTION(BlueprintCallable)
	void SetParams();
	
	UFUNCTION(BlueprintCallable)
	void GetSingleObject(UPARAM(ref) FVector& start ,UPARAM(ref)  FVector& end , FVector &SingleHit , AActor* & HitActor);
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<APlayerController>ActorController;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ACharacter>NowCharacter;

	UFUNCTION(BlueprintCallable)
	void  GetNearEnemys(AActor * Target , TArray<AActor*>& NearEnemies);

	virtual FString GetLevelDescription(int32 Level) override;
	
	virtual FString GetNextLevelDescription(int32 NowLevel)override;
};
