// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuraDecalActor.generated.h"


class UDecalComponent;
UCLASS()
class GAS_GAME_API AAuraDecalActor : public AActor
{
	GENERATED_BODY()

public:
	AAuraDecalActor();

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UDecalComponent>DecalComponent;
	
};
