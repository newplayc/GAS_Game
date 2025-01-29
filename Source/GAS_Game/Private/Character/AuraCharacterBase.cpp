// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraCharacterBase.h"
#include "GAS/AuraAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "GAS/AuraAttributeSet.h"
#include "GAS/Ability/AuraGameplayAbility.h"
#include "GAS_Game/GAS_Game.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Tag/AuraGameplayTags.h"

// Sets default values
AAuraCharacterBase::AAuraCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), "WeaponHandSocket");
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Ignore);

	
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);

}

// Called when the game starts or when spawned
void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraCharacterBase::IniAbilityInfo()
{
}

UAbilitySystemComponent* AAuraCharacterBase::GetAbilitySystemComponent() const
{
	return AbilityComponent;
}

UAnimMontage* AAuraCharacterBase::GetAnimReactMontage_Implementation()
{
	return ReactAnimMontage;
}



void AAuraCharacterBase::HasDied_Implementation()
{
	Weapon->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	NetDeath();
}

void AAuraCharacterBase::DissolveMesh()
{
	
	if(IsValid(WeaponDissolve))
	{
		UMaterialInstanceDynamic * WeapoInstanceDynamic = UKismetMaterialLibrary::CreateDynamicMaterialInstance(this , WeaponDissolve);
		Weapon->SetMaterial(0, WeapoInstanceDynamic);
		TimeLineSetWeaponMaterial();
	}

	if(IsValid(MeshDissolve))
	{
		UMaterialInstanceDynamic * MeshInstanceDynamic = UKismetMaterialLibrary::CreateDynamicMaterialInstance(this , MeshDissolve);
		GetMesh()->SetMaterial(0, MeshInstanceDynamic);
		TimeLineSetMeshMaterial();
	}

}

void AAuraCharacterBase::NetDeath_Implementation()
{
	Weapon->SetSimulatePhysics(true);
	Weapon->SetEnableGravity(true);
	Weapon->SetCollisionEnabled(ECollisionEnabled::Type::PhysicsOnly);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetAllBodiesSimulatePhysics(true);

	
	DissolveMesh();
	
}

void AAuraCharacterBase::InitAttribute(UObject* Source)
{
		AbilityComponent->ApplyEffectToInit(InitalPrimaryEffect, GetPlayerLevel_Implementation() , Source);
		AbilityComponent->ApplyEffectToInit(InitalSecondaryEffect, GetPlayerLevel_Implementation() , Source);
		AbilityComponent->ApplyEffectToInit(InitalVitalEffect,GetPlayerLevel_Implementation()  ,Source);
}

FVector AAuraCharacterBase::GetWeaponSocketLocation_Implementation(FGameplayTag AttackTag)
{
	FAuraGameplayTags AllTags =  FAuraGameplayTags::Get();
	if(AttackTag.MatchesTagExact(AllTags.Montage_WeaponAttack))
	{
		return Weapon->GetSocketLocation(WeaponSocketName);
	}
	if(AttackTag.MatchesTagExact(AllTags.Montage_LeftHandAttack))
	{
		return GetMesh()->GetSocketLocation(LeftHandSocketName);
	}
	if(AttackTag.MatchesTagExact(AllTags.Montage_RightHandAttack))
	{
		return GetMesh()->GetSocketLocation(RightHandSocketName);
	}
	return FVector();
}

ECharacterClass AAuraCharacterBase::GetCharacterClass()
{
	return CharacterClass;
}

bool AAuraCharacterBase::IsDead_Implementation()
{
	return IsDead;
}

TArray<FTagMontage> AAuraCharacterBase::GetAttackMontage_Implementation()
{
	return AttackMontage;
}

void AAuraCharacterBase::SetDead_Implementation(bool bisDead)
{
	this->IsDead = bisDead;
}

UNiagaraSystem* AAuraCharacterBase::GetBloodEffect_Implementation()
{
	return BloodEffect;
}






