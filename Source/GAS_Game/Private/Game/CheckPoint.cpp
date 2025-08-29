// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/CheckPoint.h"

#include "Components/SphereComponent.h"
#include "GAS_Game/GAS_Game.h"
#include "Interface/PlayerInterface.h"




ACheckPoint::ACheckPoint(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
	CheckMesh = CreateDefaultSubobject<UStaticMeshComponent>("CheckMesh");
	CheckMesh->SetupAttachment(RootComponent);
	CheckMesh->SetCollisionObjectType(ECC_WorldStatic);
	CheckMesh->SetCollisionResponseToChannel(ECC_Camera , ECR_Ignore);
	CheckMesh->SetCollisionResponseToChannel(ECC_Projectile , ECR_Overlap);
	
	CollisionMesh = CreateDefaultSubobject<USphereComponent>("CollisonMesh");
	CollisionMesh->SetupAttachment(CheckMesh);
	
	CollisionMesh->SetCollisionObjectType(ECC_WorldStatic);
	CollisionMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionMesh->SetCollisionResponseToChannel(ECC_Pawn ,ECR_Overlap);

}

void ACheckPoint::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);
	Ar << bFirst;
}


void ACheckPoint::BeginPlay()
{
	Super::BeginPlay();
	CollisionMesh->OnComponentBeginOverlap.AddDynamic(this ,&ACheckPoint::OnSphereOverlap);
	CollisionMesh->OnComponentEndOverlap.AddDynamic(this ,&ACheckPoint::OnEndOVerlap);
}



void ACheckPoint::OnSphereOverlap( UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	SomeOneInOut(true);
	if(OtherActor->Implements<UPlayerInterface>())
	{
		//人物触发保存
		IPlayerInterface::Execute_SavePlayState(OtherActor , PlayerStartTag);
		
	}
	
}

void ACheckPoint::OnEndOVerlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor->Implements<UPlayerInterface>())
	{
		SomeOneInOut(false);
	}
}



UMaterialInstanceDynamic *  ACheckPoint::CreatDynamicInstance()
{
	UMaterialInstanceDynamic * MaterialInstanceDynamic = UMaterialInstanceDynamic::Create(CheckMesh->GetMaterial(0) , this);
	return MaterialInstanceDynamic;
}

void ACheckPoint::SomeOneInOut(bool IsIn)
{
	
	if(!bFirst)
	{
		bFirst = true;
		DynamicMaterial = CreatDynamicInstance();
		CheckMesh->SetMaterial(0 ,DynamicMaterial.Get());
	}

	ChangeDynamicMaterial(DynamicMaterial.Get() , IsIn);
	
}
