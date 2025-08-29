// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "MapEntrance.generated.h"

class USphereComponent;
/**
 * 
 */
UCLASS()
class AMapEntrance : public APlayerStart
{
	GENERATED_BODY()
public:


	AMapEntrance(const FObjectInitializer& ObjectInitializer);

	virtual  void BeginPlay() override;

	
	UPROPERTY(VisibleAnywhere , BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent>MapEntraceMeshComponent;
	
	UPROPERTY(VisibleAnywhere , BlueprintReadOnly)
	TObjectPtr<USphereComponent>SphereComponent;
	
	UPROPERTY(EditDefaultsOnly)
	FName DefaultPlayerStart;

	UPROPERTY(EditDefaultsOnly)
	FString DestinationMapName;

	UFUNCTION()
	void OnSphereOverlap( UPrimitiveComponent*  OverlappedComponent, AActor*  OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &  SweepResult);
};
