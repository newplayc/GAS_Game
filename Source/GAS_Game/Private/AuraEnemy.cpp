// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraEnemy.h"
#include "AuraAbilitySystemComponent.h"
#include "AuraAttributeSet.h"
void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();
	AbilityComponent->InitAbilityActorInfo(this, this);
}
AAuraEnemy::AAuraEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilityComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitysysComponent");
	AbilityComponent->SetIsReplicated(true);
	AbilityComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);


	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");

	
}

void AAuraEnemy::HeightLightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(250);
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(250);
}

void AAuraEnemy::UnHeightLightActor()
{

	// bShouldHeightActor = false;

	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}
