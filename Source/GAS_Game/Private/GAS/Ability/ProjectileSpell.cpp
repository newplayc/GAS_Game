// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Ability/ProjectileSpell.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile/Projectile.h"
#include "Interface/ICombatInterface.h"




void UProjectileSpell::CreatFireBolt(FTransform &SpawnTransform, AActor * Target, const FVector& TargetLocation)
{
	// 生成 投射物 
	AProjectile* Projectile = GetWorld()->SpawnActorDeferred<AProjectile>(
	ProjectileClass,
	SpawnTransform,
	GetOwningActorFromActorInfo(),
	Cast<APawn>(GetOwningActorFromActorInfo()),
	ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	Projectile->EffectParams = MakeDefaultEffectParams();
	if(Target)
	{
		Projectile->ProjectileMoveCom->HomingTargetComponent = Target->GetRootComponent();
	}
	else
	{
		Projectile->TempSceneComponent = NewObject<USceneComponent>(USceneComponent::StaticClass());
		Projectile->TempSceneComponent->SetWorldLocation(TargetLocation);
		Projectile->ProjectileMoveCom->HomingTargetComponent = Projectile->TempSceneComponent;
	}
	Projectile->ProjectileMoveCom->HomingAccelerationMagnitude = SpreadSpeed;
	Projectile->ProjectileMoveCom->bIsHomingProjectile = true;
	Projectile->FinishSpawning(SpawnTransform);
}

void UProjectileSpell::SpawnFireBolt(const FVector & TargetLocation, FGameplayTag SocketTag, AActor * Target, bool bPitchOverride, float PitchOverride)
{
	
	if (!GetAvatarActorFromActorInfo()->HasAuthority()){return;}
	
	FVector WeaponSocketLocation = IICombatInterface::Execute_GetWeaponSocketLocation( GetAvatarActorFromActorInfo(), SocketTag);
	FRotator SpawnRotator = (TargetLocation - WeaponSocketLocation).Rotation();

	// 调整 一些 高度
	if(bPitchOverride){SpawnRotator.Pitch = PitchOverride;}
	FVector Forward = SpawnRotator.Vector();

	// 添加 一点旋转
	FVector LeftSpeard = Forward.RotateAngleAxis(-ProjectileSpread , FVector::UpVector);
	FVector RightSpead = Forward.RotateAngleAxis(ProjectileSpread , FVector::UpVector);
	int32 NumsProjectile = ProjectileNums.GetValueAtLevel(GetAbilityLevel());
	float DeltaSpread = ProjectileSpread / (NumsProjectile - 1);
	FTransform SpawnTransform;
	
	for(;NumsProjectile > 0 ; NumsProjectile--)
	{
		SpawnTransform.SetLocation(WeaponSocketLocation);
		LeftSpeard = LeftSpeard.RotateAngleAxis(DeltaSpread  , FVector::UpVector);
		SpawnTransform.SetRotation(LeftSpeard.Rotation().Quaternion());
		CreatFireBolt(SpawnTransform ,Target , TargetLocation);
	}
	
}
