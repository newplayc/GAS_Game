// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AuraAiController.generated.h"

/**
 * 
 */
UCLASS()
class GAS_GAME_API AAuraAiController : public AAIController
{
	GENERATED_BODY()
protected:

	 AAuraAiController();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	TObjectPtr<UBehaviorTreeComponent> BehaviorTree;
	
};
