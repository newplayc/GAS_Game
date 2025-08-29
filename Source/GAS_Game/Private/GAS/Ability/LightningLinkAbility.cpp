// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Ability/LightningLinkAbility.h"
#include "GameFramework/Character.h"
#include "Interface/ICombatInterface.h"
#include "Kismet/KismetSystemLibrary.h"


void ULightningLinkAbility::SetParams()
{
	ActorController = CurrentActorInfo->PlayerController.Get();
	NowCharacter = Cast<ACharacter>(CurrentActorInfo->AvatarActor);
}

void ULightningLinkAbility::GetSingleObject( FVector& start,  FVector& end, FVector& SingleHit , AActor  *& HitActor)
{
	if(!GetAvatarActorFromActorInfo()->HasAuthority())return;
	TArray<AActor*>Ignore;
	Ignore.Add(NowCharacter);
	FHitResult HitResult;

	
	UKismetSystemLibrary::SphereTraceSingle(
		NowCharacter,
		start,
		end ,
		LightningTraceRadius ,
		ETraceTypeQuery::TraceTypeQuery3 ,
	false ,
		Ignore ,
		EDrawDebugTrace::ForDuration ,
		HitResult ,
		true);

	SingleHit = HitResult.Location;
	HitActor = HitResult.GetActor();
	
}

void ULightningLinkAbility::GetNearEnemys(AActor* Target , TArray<AActor*>& NearEnemies)
{

	if(!GetAvatarActorFromActorInfo()->HasAuthority())return;
	TArray<AActor*>Ignore;
	Ignore.Add(NowCharacter);
	Ignore.Add(Target);
	
	TArray<FHitResult>HitResults;
	
	FVector Start = Target->GetActorLocation();
	UKismetSystemLibrary::SphereTraceMulti(
		GetAvatarActorFromActorInfo() ,
		Start ,
		Start ,
		LinkNearEnemyRadius ,
		TraceTypeQuery3 ,
		false,
		Ignore,
		EDrawDebugTrace::ForDuration,
		HitResults,
		true);

	for(FHitResult Hit : HitResults)
	{
		AActor * HitActor = Hit.GetActor();
		if(HitActor->Implements<UICombatInterface>())
		{
			if(NearEnemies.Num() < LinkNums)
			{
				NearEnemies.AddUnique(HitActor);
			}
		}
	}
}

FString ULightningLinkAbility::GetLevelDescription(int32 Level)
{
	SpellDescription = FString("Link a Lightning line With Target Enemy And Cause Duration Damage While Link Near Enemies");

	Damage = DamageValue.GetValueAtLevel(Level);
	
	GetCostGameplayEffect()->Modifiers[0].ModifierMagnitude.GetStaticMagnitudeIfPossible(Level , ManaCost);

	return FString::Printf(TEXT("<TEXT>Description:%s</>\n"
							 "<TEXT>LightningDamage: Per</><Num>%f</><TEXT>Second Cause</><Damage>%f</>\n"
		"<TEXT>ManaCost: </><Mana>%f</>\n"
  "<TEXT>LinkEnemy: </><Num>%d</>\n"
  "<TEXT>Level: </><Level>%d</>"),
		*SpellDescription ,DamageFrequency ,Damage, ManaCost,LinkNums,Level);
}

FString ULightningLinkAbility::GetNextLevelDescription(int32 NowLevel)
{
	NextSpellDescription =  FString("Cause More Damage And Link More Enemies");
	return FString::Printf(TEXT("<TEXT>%s</>\n<TEXT>Next Level: </><Level>%d</>"),*NextSpellDescription ,NowLevel+1);
}
