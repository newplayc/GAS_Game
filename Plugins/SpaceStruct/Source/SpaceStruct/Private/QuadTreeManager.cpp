// Fill out your copyright notice in the Description page of Project Settings.

#include "QuadTreeManager.h"

#include "GeometryTypes.h"
#include "LeafActor.h"
#include "QuadTreeNode.h"
#include "Kismet/KismetMathLibrary.h"

AQuadTreeManager::AQuadTreeManager()
	: CurrentActorCount(0)
{
	PrimaryActorTick.bCanEverTick = true;

	RootCom = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = RootCom;

	Checker = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Checker"));
	Checker->SetupAttachment(RootCom);
	Checker->SetSimulatePhysics(true);
	Checker->Mobility = EComponentMobility::Movable;
	Checker->bIgnoreRadialForce = true;
	Checker->bIgnoreRadialImpulse= true;
	Checker->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	Checker->SetEnableGravity(false);
	Checker->SetAngularDamping(12);
	Checker->SetLinearDamping(0.3);

	SpawnPoint1 = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPoint1"));
	SpawnPoint1->SetupAttachment(RootCom);
	
	SpawnPoint2 = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPoint2"));
	SpawnPoint2->SetupAttachment(RootCom);
	
	SpawnPoint3 = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPoint3"));
	SpawnPoint3->SetupAttachment(RootCom);
	
	SpawnPoint4 = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPoint4"));
	SpawnPoint4->SetupAttachment(RootCom);


}

void AQuadTreeManager::BeginPlay()
{
	Super::BeginPlay();
	
	// 初始化重生位置
	RespawnLocations.Reserve(4);
	RespawnLocations.Add(SpawnPoint1->GetComponentLocation());
	RespawnLocations.Add(SpawnPoint2->GetComponentLocation());
	RespawnLocations.Add(SpawnPoint3->GetComponentLocation());
	RespawnLocations.Add(SpawnPoint4->GetComponentLocation());
	// 初始化边界
	InitializeBounds();
	
	// 创建四叉树根节点
	const FVector TreeCenter = GetActorLocation();
	const FVector TreeExtent(Width * 0.5, Height * 0.5, 2.0);
	QuadTreeRoot = MakeShared<QuadTreeNode>(TreeCenter, TreeExtent, nullptr, 0);
	
	// 预分配Actor数组
	SpawnedActors.Reserve(MaxActorCount);
	
	// 启动定时器
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().SetTimer(SpawnTimerHandle, this, &ThisClass::SpawnActorsTick, SpawnRate, true);
		World->GetTimerManager().SetTimer(MoveTimerHandle, this, &ThisClass::MoveActorsTick, 2.0f, true);
	}
}

void AQuadTreeManager::InitializeBounds()
{
	const FVector Center = GetActorLocation();
	const double HalfWidth = Width * 0.5;
	const double HalfHeight = Height * 0.5;
	
	Bounds = FBox(
		FVector(Center.X - HalfWidth, Center.Y - HalfHeight , Center.Z),
		FVector(Center.X + HalfWidth, Center.Y + HalfHeight,Center.Z)
	);
}

FVector AQuadTreeManager::GetRandomLocationInBounds() const
{
	const FVector RandomPoint = FMath::RandPointInBox(Bounds);
	return FVector(RandomPoint.X, RandomPoint.Y, GetActorLocation().Z + 5.0);
}
void AQuadTreeManager::SpawnActorsTick()
{
	if (CurrentActorCount >= MaxActorCount)
	{
		if (UWorld* World = GetWorld())
		{
			World->GetTimerManager().ClearTimer(SpawnTimerHandle);
		}
		return;
	}

	if (!LeafActorClass || !QuadTreeRoot.IsValid())
	{
		return;
	}

	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	const FVector SpawnLocation = GetRandomLocationInBounds();

	if (ALeafActor* NewActor = World->SpawnActor<ALeafActor>(LeafActorClass, SpawnLocation, FRotator::ZeroRotator))
	{
		SpawnedActors.Add(NewActor);
		QuadTreeRoot->Insert(NewActor);
		++CurrentActorCount;
	}
}

void AQuadTreeManager::MoveActorsTick()
{
	if (!QuadTreeRoot.IsValid())
	{
		return;
	}


	for (ALeafActor* Actor : SpawnedActors)
	{
		if (Actor && Actor->MeshComponent)
		{
			// 给所有生成的Actor随机速度
			const FVector RandomVelocity = UKismetMathLibrary::RandomUnitVector() * FVector(MoveSpeed ,MoveSpeed , 0) ;
			Actor->MeshComponent->SetPhysicsLinearVelocity(RandomVelocity);
		}
	}

	// 处理逃逸的Actor
	
	if (QuadTreeRoot->EscapeActors.Num() > 0)
	{
		TArray<ALeafActor*>NotIn;
		for (ALeafActor* EscapedActor : QuadTreeRoot->EscapeActors)
		{
			if (EscapedActor && RespawnLocations.Num() > 0)
			{
				const int32 RandomIndex = FMath::RandRange(0, RespawnLocations.Num() - 1);
				EscapedActor->SetActorLocation(RespawnLocations[RandomIndex]);
				EscapedActor->MeshComponent->SetPhysicsLinearVelocity(FVector::Zero());
				if(!QuadTreeRoot->Insert(EscapedActor))
				{
					NotIn.AddUnique(EscapedActor);
				}
			}
		}
		QuadTreeRoot->EscapeActors.Empty();
		QuadTreeRoot->EscapeActors = MoveTemp(NotIn);
	}

	// 移动检查器
	if (Checker)
	{
		Checker->SetPhysicsLinearVelocity(UKismetMathLibrary::RandomUnitVector() * FVector(MoveSpeed ,MoveSpeed , 0));
		if (!QuadTreeRoot->IsInBounds(Checker->GetComponentLocation()) && RespawnLocations.Num() > 0)
		{
			const int32 RandomIndex = FMath::RandRange(0, RespawnLocations.Num() - 1);
			Checker->SetWorldLocation(RespawnLocations[RandomIndex]);
			Checker->SetPhysicsLinearVelocity(FVector::Zero());
		}
	}
}


void AQuadTreeManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!QuadTreeRoot.IsValid() || !Checker)
	{
		return;
	}

	// 更新四叉树
	QuadTreeRoot->Update();
	
	// 检查范围内的对象
	const FVector CheckerLocation = Checker->GetComponentLocation();
	QuadTreeRoot->CheckInRange(CheckerLocation, CheckRadius, true);
	
	// 绘制调试信息
	QuadTreeRoot->DrawDebug(this);
}

