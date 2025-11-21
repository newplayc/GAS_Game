// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LeafActor.generated.h"

UCLASS()
class SPACESTRUCT_API ALeafActor : public AActor
{
	GENERATED_BODY()
public:
	ALeafActor();
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent * MeshComponent;

	bool HasCollision(const FVector& Orign , float Radious) const;
	
	UPROPERTY(EditDefaultsOnly)
	UMaterial * ActiveMat;

	UPROPERTY(EditDefaultsOnly)
	UMaterial * DefaultMat;

	void Active(bool Active) const;
};
