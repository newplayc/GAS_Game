// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PointsCollection.generated.h"

UCLASS()
class GAS_GAME_API APointsCollection : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APointsCollection();


	// 获得可放物体的点位从上到下
	UFUNCTION(BlueprintPure ,BlueprintCallable)
	void  GetReachablePointsLocation(int32 NumsPoint , float YOverride,TArray<USceneComponent*>&SceneComs);

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent>Pt_0;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent>Pt_1;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent>Pt_2;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent>Pt_3;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent>Pt_4;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent>Pt_5;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent>Pt_6;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent>Pt_7;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent>Pt_8;
	UPROPERTY(VisibleAnywhere)
    TObjectPtr<USceneComponent>Pt_9;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent>Pt_10;
	UPROPERTY()
	TArray<USceneComponent*>PointComArray;
};
