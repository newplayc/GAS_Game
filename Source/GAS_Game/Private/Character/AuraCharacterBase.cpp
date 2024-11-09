// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraCharacterBase.h"
#include "GAS/AuraAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "GAS/AuraAttributeSet.h"
#include "GAS_Game/GAS_Game.h"
#include "Kismet/KismetMaterialLibrary.h"

// Sets default values
AAuraCharacterBase::AAuraCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), "WeaponHandSocket");
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
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

void AAuraCharacterBase::Died()
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
		AbilityComponent->ApplyEffectToInit(InitalPrimaryEffect, 1 , Source);
		AbilityComponent->ApplyEffectToInit(InitalSecondaryEffect, 1 , Source);
		AbilityComponent->ApplyEffectToInit(InitalVitalEffect,1  ,Source);
}

FVector AAuraCharacterBase::GetWeaponSocketLocation()
{
	return Weapon->GetSocketLocation(WeaponSocketName);
}






