// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/MapEntrance.h"

#include "AuraGameInstance.h"
#include "Components/SphereComponent.h"
#include "Game/AuraGameModeBase.h"
#include "GAS_Game/GAS_Game.h"
#include "Kismet/GameplayStatics.h"


AMapEntrance::AMapEntrance(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{

	PrimaryActorTick.bCanEverTick = false;
	MapEntraceMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("EntraceMesh");
	MapEntraceMeshComponent->SetupAttachment(RootComponent);
	MapEntraceMeshComponent->SetCollisionObjectType(ECC_WorldStatic);
	MapEntraceMeshComponent->SetCollisionResponseToChannel(ECC_Camera , ECR_Ignore);
	MapEntraceMeshComponent->SetCollisionResponseToChannel(ECC_Projectile , ECR_Overlap);

	
	SphereComponent = CreateDefaultSubobject<USphereComponent>("Sphere");
	SphereComponent->SetupAttachment(MapEntraceMeshComponent);
	SphereComponent->SetCollisionObjectType(ECC_WorldStatic);
	SphereComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComponent->SetCollisionResponseToChannel(ECC_Pawn ,ECR_Overlap);
}
void AMapEntrance::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AMapEntrance::OnSphereOverlap);
}

void AMapEntrance::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(UAuraGameInstance * Gi = Cast<UAuraGameInstance>(GetGameInstance()))
	{
		if(AAuraGameModeBase * Gm = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(this)))
		{
			Gi->PlayerStartTag = DefaultPlayerStart;
			{
				Gm->EntryGame(DestinationMapName);
			}
		}
	}
	
}
