// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
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
	SphereComp->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);
	SphereComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Overlap);
	SphereComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	SphereComp->SetCollisionObjectType(ECollisionChannel::ECC_EngineTraceChannel1);
	ProjectileMoveCom = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMoveComponent");
	ProjectileMoveCom->InitialSpeed = 550.f;
	ProjectileMoveCom->MaxSpeed = 550.f;
	ProjectileMoveCom->ProjectileGravityScale = 0.f;
	SetLifeSpan(lifeSpanTime);


}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	AudioC = UGameplayStatics::SpawnSoundAttached(LoopingSound, RootComponent);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this ,&AProjectile::OnSphereOverlap);
	
}

void AProjectile::Destroyed()
{

	if (!bHit)
	{
		UKismetSystemLibrary::PrintString(this, "Overlap", true, true, FLinearColor::Red, 50.f);
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation());
		AudioC->Stop();
	}
	Super::Destroyed();
	
}

void AProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UKismetSystemLibrary::PrintString(this, "Overlap",true , true ,FLinearColor::Red, 50.f);
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, GetActorLocation());
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ImpactEffect, GetActorLocation());
	AudioC->Stop();
	if (HasAuthority())
	{
		Destroy();
	}
	else
	{
		bHit = true;
	}
}

