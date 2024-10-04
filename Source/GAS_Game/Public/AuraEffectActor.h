// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"
class USphereComponent;
class UStaticMeshComponent;
class UGameplayEffect;
UCLASS()
class GAS_GAME_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAuraEffectActor();

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* Actor, TSubclassOf<UGameplayEffect>GameplayEffect);

	UPROPERTY(EditAnywhere,BlueprintReadOnly ,Category = "EffectToApply" )
	TSubclassOf<UGameplayEffect>AppliedEffect;
};
