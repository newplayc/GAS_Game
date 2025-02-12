// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/FindNearstEnemy.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interface/EnemyInterface.h"
#include "Interface/ICombatInterface.h"
#include "Kismet/GameplayStatics.h"

void UFindNearstEnemy::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	AActor * AiOwner = OwnerComp.GetAIOwner()->GetPawn();
	bool IsRanger  = false;
	if(AiOwner->Implements<UICombatInterface>())
	{
		IsRanger = IICombatInterface::Execute_GetCharacterClass(AiOwner) == ECharacterClass::Ranger;
	}
	
	FName EnemyName = AiOwner->ActorHasTag(FName("Player")) ? FName("Enemy") : FName("Player");

	TArray<AActor*> EnemysFound;
	UGameplayStatics::GetAllActorsWithTag(this ,EnemyName ,EnemysFound);
	if(EnemysFound.Num() <0)return;
	
	float NearstDistance = 1000000000.f;
	AActor * NearstActor = nullptr;
	for(AActor * Actor : EnemysFound)
	{
		if(IICombatInterface::Execute_IsDead(Actor))continue;
		if(AiOwner->GetDistanceTo(Actor) < NearstDistance)
		{
			NearstActor = Actor;
			NearstDistance = AiOwner->GetDistanceTo(Actor);
		}
	}
	IEnemyInterface::Execute_SetTargetActor(AiOwner,NearstActor);

	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(NearestDistanceKey.SelectedKeyName , NearstDistance);
	OwnerComp.GetBlackboardComponent()->SetValueAsObject(NeareatActorKey.SelectedKeyName ,NearstActor);
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(IsRanegr.SelectedKeyName ,IsRanger);
}
