// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Ability/ProjectileSpell.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Projectile/Projectile.h"
#include "Interface/ICombatInterface.h"


void UProjectileSpell::SpawnFireBolt(const FVector & TargetLocation , FGameplayTag SocketTag)
{
	
	
	if (!GetAvatarActorFromActorInfo()->HasAuthority())
	{
		return;
	}
	FTransform SpawnTransform;


	FVector WeaponSocketLocation = IICombatInterface::Execute_GetWeaponSocketLocation( GetAvatarActorFromActorInfo(), SocketTag);
	FRotator SpawnRotator = (TargetLocation - WeaponSocketLocation).Rotation();

	SpawnTransform.SetLocation(WeaponSocketLocation);
	SpawnTransform.SetRotation(SpawnRotator.Quaternion());
	AProjectile* Projectile = GetWorld()->SpawnActorDeferred<AProjectile>(ProjectileClass, SpawnTransform, GetOwningActorFromActorInfo(),
		Cast<APawn>(GetOwningActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	
	
	Projectile->EffectParams = MakeDefaultEffectParams();
    
	Projectile->FinishSpawning(SpawnTransform);


}
