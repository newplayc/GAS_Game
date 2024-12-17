// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/Projectile.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet\GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereCom");
	RootComponent = SphereComp;
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);
	SphereComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Overlap);
	SphereComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	SphereComp->SetCollisionObjectType(ECollisionChannel::ECC_EngineTraceChannel1);
	
	ProjectileMoveCom = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMoveComponent");
	ProjectileMoveCom->InitialSpeed = 550.f;
	ProjectileMoveCom->MaxSpeed = 550.f;
	ProjectileMoveCom->ProjectileGravityScale = 0.f;
	



}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	
	Super::BeginPlay();
	SetLifeSpan(lifeSpanTime);
	AudioC = UGameplayStatics::SpawnSoundAttached(LoopingSound, RootComponent);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this ,&AProjectile::OnSphereOverlap);
	
}

void AProjectile::Destroyed()
{
	
	if (!bHit && !HasAuthority())
	{
		
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation());
		if(AudioC)
		{
			AudioC->Stop();
		}

		
	}
	Super::Destroyed();
	
}

void AProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if(!bHit)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, GetActorLocation());
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ImpactEffect, GetActorLocation());
		if(AudioC) AudioC->Stop();
	}
	if (HasAuthority())
	{
		if(UAbilitySystemComponent * ASC =  UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
		{
			ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
		Destroy();
	}
	else
	{
		bHit = true;
	}
	
}

