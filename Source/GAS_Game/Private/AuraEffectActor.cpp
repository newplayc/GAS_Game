// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraEffectActor.h"


// Sets default values
AAuraEffectActor::AAuraEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("Root"));
	
}

void AAuraEffectActor::OnOverlap(AActor * TargetActor)
{
	if (InstantlyEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantlyGameplayEffect);
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffect);
	}
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffect);
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{


	if (InstantlyEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantlyGameplayEffect);
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffect);
	}
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffect);
	}
	if(InfiniteEffectRemovePolicy == EEffectRemovePolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent * ASC  = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (!ASC)return;
		TArray<FActiveGameplayEffectHandle>DelArray;
		for (auto ComPair : InfiniteComponents)
		{
			if (ComPair.Value == ASC)
			{
				ASC->RemoveActiveGameplayEffect(ComPair.Key,1);
				DelArray.Add(ComPair.Key);
			}
		}
		for (auto Del : DelArray)
		{
			InfiniteComponents.Remove(Del);
		}
	}
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* Actor, TSubclassOf<UGameplayEffect> GameplayEffect)
{
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Actor);
	if (!ASC)return;

	check(GameplayEffect)
	FGameplayEffectContextHandle GECH = ASC->MakeEffectContext();
	GECH.AddSourceObject(this);
	const FGameplayEffectSpecHandle GESH = ASC->MakeOutgoingSpec(GameplayEffect, 1.f, GECH);
	const FActiveGameplayEffectHandle ActiveEffectHandle = ASC->ApplyGameplayEffectSpecToSelf(*GESH.Data.Get());
	const bool IsInfinite = GESH.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
	if (IsInfinite)
	{
		InfiniteComponents.Add(MakeTuple(ActiveEffectHandle, ASC));
	}

}


// Called when the game starts or when spawned
void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();

}





