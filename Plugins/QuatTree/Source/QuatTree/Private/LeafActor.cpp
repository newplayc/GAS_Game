// Fill out your copyright notice in the Description page of Project Settings.


#include "LeafActor.h"


// Sets default values
ALeafActor::ALeafActor()
{
	PrimaryActorTick.bCanEverTick = false;
	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	
	RootComponent = MeshComponent;
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::Type::PhysicsOnly);
	MeshComponent->Mobility =EComponentMobility::Type::Movable;
	MeshComponent->SetConstraintMode(EDOFMode::Type::XYPlane);
	MeshComponent->SetSimulatePhysics(true);
	
}
 
void ALeafActor::BeginPlay()
{
	Super::BeginPlay();
}
void ALeafActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALeafActor::Active(bool Active) const
{
	if(Active)
		MeshComponent->SetMaterial(0,ActiveMat);
	else
		MeshComponent->SetMaterial(0 , DefaultMat);
}

