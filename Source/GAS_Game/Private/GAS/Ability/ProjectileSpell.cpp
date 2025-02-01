// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Ability/ProjectileSpell.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Projectile/Projectile.h"
#include "Interface/ICombatInterface.h"
#include "Tag/AuraGameplayTags.h"


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
	
	
	if(UAbilitySystemComponent* ASC =  UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo()))
	{
		FGameplayEffectContextHandle EffContextHanle =  ASC->MakeEffectContext();
		EffContextHanle.SetAbility(this);
		EffContextHanle.AddSourceObject(GetAvatarActorFromActorInfo());
		Projectile->SpecHandle =  ASC->MakeOutgoingSpec(DamageEffect , GetAbilityLevel() , EffContextHanle);
	}
		
	for(auto Data : DamageTypes)
	{
		float DataValue = Data.Value.GetValueAtLevel(GetAbilityLevel());
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(Projectile->SpecHandle ,Data.Key , DataValue);
	}
	Projectile->FinishSpawning(SpawnTransform);


}
