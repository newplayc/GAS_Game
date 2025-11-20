// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LeafActor.generated.h"

UCLASS()
class QUATTREE_API ALeafActor : public AActor
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
	
	UPROPERTY(EditDefaultsOnly)
	UMaterial * ActiveMat;

	UPROPERTY(EditDefaultsOnly)
	UMaterial * DefaultMat;

	void Active(bool Active) const;
};
