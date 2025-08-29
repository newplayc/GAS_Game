// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "FindNearstEnemy.generated.h"

/**
 *  选择  最近 的敌人  并且修改 黑板键
 */
UCLASS()
class UFindNearstEnemy : public UBTService
{
	GENERATED_BODY()

	public:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector NearestDistanceKey;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector NeareatActorKey;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector IsRanegr;
};
