// Fill out your copyright notice in the Description page of Project Settings.


#include "QuadTreeManager.h"
#include "LeafActor.h"
#include "QuadTreeNode.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AQuadTreeManager::AQuadTreeManager()
{
	PrimaryActorTick.bCanEverTick = true;


	RootCom = CreateDefaultSubobject<USceneComponent>("RootComponent");
	RootComponent = RootCom;


	SceneComponent1 = CreateDefaultSubobject<USceneComponent>("RootComponent1");
	SceneComponent2 = CreateDefaultSubobject<USceneComponent>("SceneComponent2");
	SceneComponent3 = CreateDefaultSubobject<USceneComponent>("SceneComponent3");
	
	
	Checker = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Checker->SetSimulatePhysics(true);
	Checker->Mobility  = EComponentMobility::Type::Movable;
	Checker->SetConstraintMode(EDOFMode::XYPlane);
	Checker->SetCollisionEnabled(ECollisionEnabled::Type::PhysicsOnly);
}

void AQuadTreeManager::BeginPlay()
{
	Super::BeginPlay();
	RandLocations.Add(SceneComponent1->GetComponentLocation());
	RandLocations.Add(SceneComponent2->GetComponentLocation());
	RandLocations.Add(SceneComponent3->GetComponentLocation());

	
	Root = MakeShareable(new QuadTreeNode(GetActorLocation()  , FVector(Width/2 , Height/2 , 2) , nullptr,0));
	FVector ActorLoc = GetActorLocation();
	Maxx = ActorLoc.X + Width / 2;
	Minx = ActorLoc.X - Width / 2;
	Maxy = ActorLoc.Y + Height / 2;
	Miny = ActorLoc.Y - Height / 2;
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this,  &ThisClass::SpawnActorsInTimer ,SpawnRate , true);
	GetWorld()->GetTimerManager().SetTimer(MoveTimerHandle , this, &ThisClass::MoveActor , 2.f , true);
}
 
void AQuadTreeManager::SpawnActorsInTimer()
{
	if(NowNums < ActorNum)
	{
		double RandX = FMath::FRandRange(Minx , Maxx);
		double RandY = FMath::FRandRange(Miny , Maxy);
		ALeafActor * LA =  GetWorld()->SpawnActor<ALeafActor>(LeafClass,FVector(RandX , RandY , GetActorLocation().Z + 5) , FRotator());
		Objs.Add(LA);
		Root->Insert(LA);
		NowNums++;	
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
	}
}

void AQuadTreeManager::MoveActor()
{

	for(const auto & obj : Objs)
	{
		obj->MeshComponent->SetPhysicsLinearVelocity(UKismetMathLibrary::RandomUnitVector() * Speed);
	}

	
	for(const auto & Escap: Root->EscapeActors)
	{
		int32 Rand = FMath::RandRange(0 , 2);
		Escap->SetActorLocation(RandLocations[Rand]);
		Root->Insert(Escap);
	}
	Root->EscapeActors.Empty();

	
	Checker->SetPhysicsLinearVelocity(UKismetMathLibrary::RandomUnitVector() * Speed);
	if(!Root->IsInBound(Checker->GetComponentLocation()))
	{
		int32 Rand = FMath::RandRange(0 , RandLocations.Num() -1);
		Checker->SetWorldLocation(RandLocations[Rand]);
	}
	
}


void AQuadTreeManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Root->update();
	Root->CheckIn(Checker->GetComponentLocation() , CheckBaseLegth / 2 , true);
	Root->Tick(this);
}

