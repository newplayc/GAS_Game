// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileSpell.h"
#include "Projectile.h"
#include "ICombatInterface.h"



void UProjectileSpell::SpawnFireBolt(const FVector & TargetLocation)
{
	
	if (!GetAvatarActorFromActorInfo()->HasAuthority())
	{
		return;
	}
	FTransform SpawnTransform;

	IICombatInterface* Ac = Cast<IICombatInterface>(GetAvatarActorFromActorInfo());
	if (!Ac)return;
	FVector WeaponSocketLocation = Ac->GetWeaponSocketLocation();
	FRotator SpawnRotator = (TargetLocation - WeaponSocketLocation).Rotation();
	SpawnRotator.Pitch = 0.f;
	SpawnTransform.SetLocation(WeaponSocketLocation);
	SpawnTransform.SetRotation(SpawnRotator.Quaternion());
	AProjectile* Projectile = GetWorld()->SpawnActorDeferred<AProjectile>(ProjectileClass, SpawnTransform, GetOwningActorFromActorInfo(),
		Cast<APawn>(GetOwningActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	Projectile->FinishSpawning(SpawnTransform);


}
