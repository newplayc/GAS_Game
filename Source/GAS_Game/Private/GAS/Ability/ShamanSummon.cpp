// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Ability/ShamanSummon.h"

#include "Kismet/KismetSystemLibrary.h"

TArray<FVector> UShamanSummon::GetSpawnLocations()
{
	TArray<FVector>Locations;

	FVector NowLocation = GetAvatarActorFromActorInfo()->GetActorLocation();
	FVector ForwardVector = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	FVector LeftBorderVector = ForwardVector.RotateAngleAxis( -SummonSpread  / 2 ,  FVector::UpVector);
	// FVector RightBorderBector = ForwardVector.RotateAngleAxis( SummonSpread  / 2 ,  FVector::UpVector);
	float space = SummonSpread  / NumSummon;
	for(int i = 0 ; i < NumSummon ; i++)
	{
		// 生成 位置 成扇形
		FVector NowVector = LeftBorderVector.RotateAngleAxis(space * i , FVector::UpVector) ;
		FVector SpawnLocation = NowLocation + NowVector * FMath::RandRange(MinDistance , MaxDistance);
		// 做 射线 检测 防止 生成 在空中
		FHitResult Hit;
		GetWorld()->LineTraceSingleByChannel(Hit, SpawnLocation , SpawnLocation + FVector::DownVector  * 200 , ECC_Visibility);
		if(Hit.bBlockingHit)
		{
			SpawnLocation = Hit.Location;
		}
		Locations.Add(SpawnLocation);
	}	

	return Locations;
}
