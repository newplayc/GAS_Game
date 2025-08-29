// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "Interface/SaveActorInterface.h"
#include "CheckPoint.generated.h"


class USphereComponent;
/**
 * 
 */
UCLASS()
class GAS_GAME_API ACheckPoint : public APlayerStart , public ISaveActorInterface
{
	
	GENERATED_BODY()
public:
	// APlayerStart 的构造函数
	ACheckPoint(const FObjectInitializer& ObjectInitializer);
	virtual void Serialize(FArchive& Ar) override;
	virtual  void BeginPlay() override;
protected:
	UPROPERTY()
	bool bFirst = false;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent>CheckMesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent>CollisionMesh;
	
	UFUNCTION()
	void OnSphereOverlap( UPrimitiveComponent*  OverlappedComponent, AActor*  OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &  SweepResult);

	UFUNCTION()
	void OnEndOVerlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void SomeOneInOut(bool IsIn);

	UFUNCTION()
	UMaterialInstanceDynamic *  CreatDynamicInstance();

	// True Is In False Is Out
	UFUNCTION(BlueprintImplementableEvent)
	void ChangeDynamicMaterial(UMaterialInstanceDynamic * Dynamic ,bool bIn);

	
	TWeakObjectPtr<UMaterialInstanceDynamic>DynamicMaterial;
	
};
