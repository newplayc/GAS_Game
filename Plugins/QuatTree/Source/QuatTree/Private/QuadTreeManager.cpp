// Fill out your copyright notice in the Description page of Project Settings.


#include "QuadTreeManager.h"
#include "LeafActor.h"
#include "QuadTreeNode.h"
#include "Kismet/KismetMathLibrary.h"



// Sets default values
AQuadTreeManager::AQuadTreeManager()
{
	
	PrimaryActorTick.bCanEverTick = true;
	Checker = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Checker->Mobility  = EComponentMobility::Type::Movable;
	Checker->SetConstraintMode(EDOFMode::XYPlane);
	Checker->SetSimulatePhysics(true);
	
}

void AQuadTreeManager::BeginPlay()
{
	Super::BeginPlay();
	Root = MakeShareable(new QuadTreeNode(GetActorLocation()  , FVector(Width/2 , Height/2 , 2) , nullptr));
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
		ALeafActor * LA =  GetWorld()->SpawnActor<ALeafActor>(LeafClass,FVector(RandX , RandY , GetActorLocation().Z) , FRotator());
		Objs.Add(LA);
		Root->Insert(LA);
		NowNums++;	
	}
	
}

void AQuadTreeManager::MoveActor()
{
	for(const auto & obj : Objs)
	{
		obj->MeshComponent->SetPhysicsLinearVelocity(UKismetMathLibrary::RandomUnitVector() * 20.f);
		if(!Root->IsInBound(obj->GetActorLocation()))
		{
			obj->SetActorLocation(GetActorLocation());
		}
	}
	Checker->SetPhysicsLinearVelocity(UKismetMathLibrary::RandomUnitVector() * 20.f);
	if(!Root->IsInBound(Checker->GetComponentLocation()))
	{
		Checker->SetRelativeLocation(FVector::Zero());
	}
}

void AQuadTreeManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Root->update();
	Root->Tick(this);

}

