// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QuadTreeManager.generated.h"

class ALeafActor;
class QuadTreeNode;

/**
 * 四叉树管理器 - 用于空间分区和碰撞检测优化
 */
UCLASS()
class SPACESTRUCT_API AQuadTreeManager : public AActor
{
	GENERATED_BODY()

public:
	AQuadTreeManager();
	virtual void Tick(float DeltaTime) override;
	
protected:
	virtual void BeginPlay() override;
	
	// 组件
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USceneComponent> RootCom;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> Checker;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USceneComponent> SpawnPoint1;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USceneComponent> SpawnPoint2;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USceneComponent> SpawnPoint3;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USceneComponent> SpawnPoint4;

	// 四叉树配置
	UPROPERTY(EditAnywhere, Category = "QuadTree", meta = (ClampMin = "100.0"))
	double Width = 2000.0;
	
	UPROPERTY(EditAnywhere, Category = "QuadTree", meta = (ClampMin = "100.0"))
	double Height = 2000.0;
	
	UPROPERTY(EditAnywhere, Category = "QuadTree", meta = (ClampMin = "1.0"))
	float CheckRadius = 600.0f;

	// 生成配置
	UPROPERTY(EditAnywhere, Category = "Spawning", meta = (ClampMin = "1"))
	int32 MaxActorCount = 100;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<ALeafActor> LeafActorClass;

	UPROPERTY(EditAnywhere, Category = "Spawning", meta = (ClampMin = "0.1"))
	float SpawnRate = 0.3f;
	
	UPROPERTY(EditAnywhere, Category = "Spawning", meta = (ClampMin = "10.0"))
	float MoveSpeed = 100.0f;

private:
	// 四叉树根节点
	TSharedPtr<QuadTreeNode> QuadTreeRoot;

	// 生成的Actor列表
	UPROPERTY()
	TArray<ALeafActor*> SpawnedActors;

	// 重生位置
	TArray<FVector> RespawnLocations;
	
	// 定时器
	FTimerHandle SpawnTimerHandle;
	FTimerHandle MoveTimerHandle;
	
	// 边界
	FBox Bounds;
	int32 CurrentActorCount;

	// 内部方法
	void SpawnActorsTick();
	void MoveActorsTick();
	void InitializeBounds();
	FVector GetRandomLocationInBounds() const;
};
