// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraEffectActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "AuraAttributeSet.h"

// Sets default values
AAuraEffectActor::AAuraEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshCom");
	SetRootComponent(StaticMeshComponent);

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereCom");
	SphereComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AAuraEffectActor::OnBeginOverLap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &AAuraEffectActor::OnEndOverLap);
}

void AAuraEffectActor::OnBeginOverLap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IAbilitySystemInterface* InterfaceActor = Cast<IAbilitySystemInterface>(OtherActor)) {
		const UAuraAttributeSet* AttributeSet = Cast<UAuraAttributeSet>(InterfaceActor->GetAbilitySystemComponent()->GetAttributeSet(UAuraAttributeSet::StaticClass()));
		check(AttributeSet);
		 UAuraAttributeSet* MutableAttribute = const_cast<UAuraAttributeSet*>(AttributeSet);
		
		MutableAttribute->SetHealth(AttributeSet->GetHealth() + 25.f);
		Destroy();
	}
	
}


void AAuraEffectActor::OnEndOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}



