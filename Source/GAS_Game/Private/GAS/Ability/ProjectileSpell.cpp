// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Ability/ProjectileSpell.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Tag/AuraGameplayTags.h"
#include "Projectile/Projectile.h"
#include "Interface/ICombatInterface.h"



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
	
	
	if(UAbilitySystemComponent* ASC =  UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo()))
	{
		FGameplayEffectContextHandle EffContextHanle =  ASC->MakeEffectContext();
		EffContextHanle.SetAbility(this);
		EffContextHanle.AddSourceObject(GetAvatarActorFromActorInfo());
		Projectile->SpecHandle =  ASC->MakeOutgoingSpec(ProjectileEffect , GetAbilityLevel() , EffContextHanle);
	}
	
	const FGameplayTag DTag  = FAuraGameplayTags::Get().Damage;
	
	const float DamageNum  = Damage.GetValueAtLevel(GetAbilityLevel());
	
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(Projectile->SpecHandle ,DTag , DamageNum);
	
	Projectile->FinishSpawning(SpawnTransform);


}
