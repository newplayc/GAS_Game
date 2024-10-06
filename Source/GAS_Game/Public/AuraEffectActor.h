// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "ActiveGameplayEffectHandle.h"
#include "AuraAttributeSet.h"
#include "AuraEffectActor.generated.h"






UENUM(BlueprintType)
enum class EEffectApplicationPolicy:uint8
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	NeverApply
};

UENUM(BlueprintType)
enum class EEffectRemovePolicy:uint8
{
	RemoveOnEndOverlap,
	NeverRemove
};

UCLASS()
class GAS_GAME_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AAuraEffectActor();


	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor * TargetActor);


	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	


	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* Actor, TSubclassOf<UGameplayEffect>GameplayEffect);



	UPROPERTY(EditAnywhere,BlueprintReadOnly ,Category = "EffectToApply" )
	TSubclassOf<UGameplayEffect>InstantlyGameplayEffect;
	UPROPERTY(EditAnywhere, BlueprintReadwrite)
	EEffectApplicationPolicy InstantlyEffectApplicationPolicy = EEffectApplicationPolicy::ApplyOnOverlap;




	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EffectToApply")
	TSubclassOf<UGameplayEffect>DurationGameplayEffect;
	UPROPERTY(EditAnywhere, BlueprintReadwrite)
	EEffectApplicationPolicy DurationEffectApplicationPolicy = EEffectApplicationPolicy::ApplyOnOverlap;




	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EffectToApply")
	TSubclassOf<UGameplayEffect>InfiniteGameplayEffect;
	UPROPERTY(EditAnywhere, BlueprintReadwrite)
	EEffectApplicationPolicy InfiniteEffectApplicationPolicy = EEffectApplicationPolicy::ApplyOnOverlap;
	UPROPERTY(EditAnywhere, BlueprintReadwrite)
	EEffectRemovePolicy InfiniteEffectRemovePolicy = EEffectRemovePolicy::RemoveOnEndOverlap;


	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> InfiniteComponents;

};
