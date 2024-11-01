// Fill out your copyright notice in the Description page of Project Settings.



#include "AuraEnemy.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AuraAbilitySystemComponent.h"
#include "AuraAttributeSet.h"
#include "AuraBlueprintFunctionLibrary.h"
#include "AuraGameplayTags.h"
#include "GameFramework/CharacterMovementComponent.h"


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
	GetCharacterMovement()->MaxWalkSpeed = EnemySpeed;
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

	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

void AAuraEnemy::IniAbilityInfo()
{
	AbilityComponent->InitAbilityActorInfo(this, this);
	InitAttribute(this);
	BindAttribute();
	UAuraBlueprintFunctionLibrary::AddStartingAbilities(this , AbilityComponent);
}

int32 AAuraEnemy::GetPlayerLevel()
{
	return Level;
}

void AAuraEnemy::InitAttribute(UObject* Source)
{
	UAuraBlueprintFunctionLibrary::SetAttributeInfo(CharacterClass , this , AbilityComponent , Level);
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
	
	AbilityComponent->RegisterGameplayTagEvent(FAuraGameplayTags::Get().Effects_React , EGameplayTagEventType::NewOrRemoved).AddUObject(this ,&AAuraEnemy::ReactTagChange);
	
	OnHealthChanged.Broadcast(AuraSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraSet->GetMaxHealth());
}

void AAuraEnemy::ReactTagChange(const FGameplayTag Tag, int32 count)
{
	GetCharacterMovement()->StopActiveMovement();
}


void AAuraEnemy::Died()
{
	Super::Died();
	SetLifeSpan(LifeSpan);
}
