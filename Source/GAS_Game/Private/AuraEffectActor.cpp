// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraEffectActor.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AuraAttributeSet.h"

// Sets default values
AAuraEffectActor::AAuraEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("Root"));
	
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* Actor, TSubclassOf<UGameplayEffect> GameplayEffect)
{
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Actor);
	if (!ASC)return;

	check(GameplayEffect)
	FGameplayEffectContextHandle GECH = ASC->MakeEffectContext();
	GECH.AddSourceObject(this);
	FGameplayEffectSpecHandle GESH = ASC->MakeOutgoingSpec(GameplayEffect, 1.f, GECH);
	ASC->ApplyGameplayEffectSpecToSelf(*GESH.Data.Get());
}


// Called when the game starts or when spawned
void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();

}





