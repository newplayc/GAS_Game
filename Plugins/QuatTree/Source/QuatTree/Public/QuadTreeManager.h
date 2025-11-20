// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QuadTreeManager.generated.h"

class ALeafActor;
class QuadTreeNode;


UCLASS()
class QUATTREE_API AQuadTreeManager : public AActor
{
	GENERATED_BODY()

public:
	AQuadTreeManager();
	virtual void Tick(float DeltaTime) override;
	
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent>Checker;
	
	UPROPERTY(EditAnywhere)
	double Width;
	
	UPROPERTY(EditAnywhere)
	double Height;
	
	UPROPERTY(EditAnywhere)
	int32 ActorNum;
	
	UPROPERTY(EditAnywhere)
	float SpawnRate = 0.3f;
	
	int32 NowNums = 0;
	
	TSharedPtr<QuadTreeNode>Root;

	void SpawnActorsInTimer();
	void MoveActor();
	
	FTimerHandle SpawnTimerHandle;
	FTimerHandle MoveTimerHandle;
	UPROPERTY(EditAnywhere)
	TSubclassOf<ALeafActor>LeafClass;

	UPROPERTY()
	TArray<ALeafActor*>Objs;

private:
	double Minx , Maxx , Miny , Maxy;
};
