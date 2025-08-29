// Fill out your copyright notice in the Description page of Project Settings.


#include "OtherActor/PointsCollection.h"

#include "AuraBlueprintFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"

APointsCollection::APointsCollection()
{
	PrimaryActorTick.bCanEverTick = false;
	Pt_0 = CreateDefaultSubobject<USceneComponent>("Pt_0");
	RootComponent = Pt_0;
	Pt_1 = CreateDefaultSubobject<USceneComponent>("Pt_1");
	Pt_1->SetupAttachment(RootComponent);
	Pt_2 = CreateDefaultSubobject<USceneComponent>("Pt_2");
	Pt_2->SetupAttachment(RootComponent);
	Pt_3 = CreateDefaultSubobject<USceneComponent>("Pt_3");
	Pt_3->SetupAttachment(RootComponent);
	Pt_4 = CreateDefaultSubobject<USceneComponent>("Pt_4");
	Pt_4->SetupAttachment(RootComponent);
	Pt_5 = CreateDefaultSubobject<USceneComponent>("Pt_5");
	Pt_5->SetupAttachment(RootComponent);
	Pt_6 = CreateDefaultSubobject<USceneComponent>("Pt_6");
	Pt_6->SetupAttachment(RootComponent);
	Pt_7 = CreateDefaultSubobject<USceneComponent>("Pt_7");
	Pt_7->SetupAttachment(RootComponent);
	Pt_8 = CreateDefaultSubobject<USceneComponent>("Pt_8");
	Pt_8->SetupAttachment(RootComponent);
	Pt_9 = CreateDefaultSubobject<USceneComponent>("Pt_9");
	Pt_9->SetupAttachment(RootComponent);
	Pt_10 = CreateDefaultSubobject<USceneComponent>("Pt_10");
	Pt_10->SetupAttachment(RootComponent);
	PointComArray.Add(Pt_0);
	PointComArray.Add(Pt_1);
	PointComArray.Add(Pt_2);
	PointComArray.Add(Pt_3);
	PointComArray.Add(Pt_4);
	PointComArray.Add(Pt_5);
	PointComArray.Add(Pt_6);
	PointComArray.Add(Pt_7);
	PointComArray.Add(Pt_8);
	PointComArray.Add(Pt_9);
	PointComArray.Add(Pt_10);
}

void APointsCollection::GetReachablePointsLocation(int32 NumsPoint, float YOverride , TArray<USceneComponent*>&SceneComs)
{
	                       
	checkf(NumsPoint <= PointComArray.Num(), TEXT("没有那么多点"));
	for(USceneComponent * pt : PointComArray)
	{
		if(SceneComs.Num() >= NumsPoint)return;
		if(pt != Pt_0)
		{
			pt->SetRelativeLocation(pt->GetRelativeLocation().RotateAngleAxis(YOverride ,FVector::UpVector));
		}
		const FVector UpLocation = FVector(pt->GetComponentLocation().X , pt->GetComponentLocation().Y , pt->GetComponentLocation().Z + 500.f);
		const FVector LowLocation = FVector(pt->GetComponentLocation().X , pt->GetComponentLocation().Y , pt->GetComponentLocation().Z - 500.f);

		TArray<AActor*>IgnoreActors;
		UAuraBlueprintFunctionLibrary::GetOverlapActors(this,GetActorLocation(),TArray<AActor*>() ,1500.f,IgnoreActors);

		
		FHitResult HitResult;
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActors(IgnoreActors);
		GetWorld()->LineTraceSingleByChannel(HitResult ,UpLocation , LowLocation ,ECC_Visibility,QueryParams);

		pt->SetWorldLocation(HitResult.ImpactPoint);
		pt->SetWorldRotation(UKismetMathLibrary::MakeRotFromZ(HitResult.ImpactNormal));

		SceneComs.Add(pt);
	}
}

