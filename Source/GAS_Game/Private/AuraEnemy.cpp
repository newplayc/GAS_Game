// Fill out your copyright notice in the Description page of Project Settings.



#include "AuraEnemy.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AuraAbilitySystemComponent.h"
#include "AuraAttributeSet.h"
#include "AuraBlueprintFunctionLibrary.h"


AAuraEnemy::AAuraEnemy()
{
	
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilityComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitysysComponent");
	AbilityComponent->SetIsReplicated(true);
	AbilityComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);


	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetMesh());

}


void AAuraEnemy::BeginPlay()
{
	Super::BeginPlay();
	IniAbilityInfo();

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

void AAuraEnemy::IniAbilityInfo()
{
	AbilityComponent->InitAbilityActorInfo(this, this);
	AbilityComponent->InitAttribute(this);
	BindAttribute();

}

int32 AAuraEnemy::GetPlayerLevel()
{
	return Level;
}

void AAuraEnemy::BindAttribute()
{
	if(UAuraUserWidget * UserWidget =  Cast<UAuraUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		UserWidget->SetWidgetController(this);
	}
	UAuraAttributeSet * AuraSet = Cast<UAuraAttributeSet>(GetAttributeSet());
	if(!AuraSet)return;
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(AuraSet->GetHealthAttribute()).AddLambda([this](const FOnAttributeChangeData & Data){
		OnHealthChanged.Broadcast(Data.NewValue);   
	}
	);
	
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(AuraSet->GetMaxHealthAttribute()).AddLambda([this](const FOnAttributeChangeData & Data){
		OnMaxHealthChanged.Broadcast(Data.NewValue);   
	}
	);

	OnHealthChanged.Broadcast(AuraSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraSet->GetMaxHealth());
}
