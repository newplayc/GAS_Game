// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"


class UNiagaraSystem;
class USoundBase;
class USphereComponent;
class UProjectileMovementComponent;


UCLASS()
class GAS_GAME_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	UPROPERTY(BlueprintReadOnly ,  meta = (ExposeOnSpawn = true))
	FGameplayEffectSpecHandle SpecHandle = nullptr;

	

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void Destroyed()override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent>ProjectileMoveCom;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent>SphereComp;
	
	UPROPERTY(EditAnywhere)
	
	TObjectPtr<UNiagaraSystem>ImpactEffect;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase>ImpactSound;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase>LoopingSound;


	UAudioComponent* AudioC = nullptr;



	
	UPROPERTY(EditAnywhere)
	float lifeSpanTime = 10.f;

	
	bool bHit = false;
	
	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
