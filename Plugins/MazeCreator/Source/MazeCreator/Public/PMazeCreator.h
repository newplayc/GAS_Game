// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <vector>

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PMazeCreator.generated.h"

struct Point
{
	int32 x;
	int32 y;
	
};

UCLASS()
class MAZECREATOR_API AMazeCreator : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMazeCreator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere , BlueprintReadOnly)
	USceneComponent * DefaultRoot;

	UPROPERTY()
	TArray<UStaticMeshComponent*>SpawnStaticMeshes;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMesh>BlockMesh;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMesh>PlaneMesh;


	UPROPERTY(EditAnywhere)
	float  MeshWidth = 50.f;
	
	UPROPERTY(EditAnywhere)
	int32 Width;

	UPROPERTY(EditAnywhere)
	int32 Height;
	
	UPROPERTY(EditAnywhere)
	float playRate = 0.3f;
	
	UPROPERTY(EditAnywhere , meta=(ToolTip = "0 使用dfs生成 拥有 明显的主路, 1  拥有更多的分岔路 , 2 拥有 方块形 的 活动区域"))
	int32 creationMode = 0;
	
	UPROPERTY()
	FTimerHandle TimerHandle;
	
	UPROPERTY(EditAnywhere , meta=(EditCondition = "creationMode == 2" ,EditConditionHides ,ClampMax =1.0 , ClampMin =0.0))
	float RoomNum = 0.f;

	UPROPERTY(EditAnywhere , meta=(EditCondition = "creationMode == 2" ,EditConditionHides,ClampMax =1.0 , ClampMin =0.0))
	float RoomSize = 0.f;
	
	// 1为 道路 0 为 墙
	std::vector<std::vector<int32>> roadArr;
	TQueue<TTuple<int32 ,int32>>taskQueue;
	static TTuple<int32 , int32,int32> GetBorderRandomLoc(int32 Width , int32 Height);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void SpawnMaze();
	virtual void DfsSpawn();
	virtual void CubeSplit();
	virtual void PrimSpawn();
	
private:
	UFUNCTION()
	void ChangeMesh();
	std::vector<std::vector<bool>>CubeFlag;
};
