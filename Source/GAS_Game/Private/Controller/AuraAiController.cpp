// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/AuraAiController.h"

#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"


AAuraAiController::AAuraAiController()
{
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>("BlackboardComponent");
	check(Blackboard);
	BehaviorTree = CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviorTree");
	check(BehaviorTree);
}
