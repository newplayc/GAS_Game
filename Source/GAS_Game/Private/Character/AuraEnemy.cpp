// Fill out your copyright notice in the Description page of Project Settings.



#include "Character/AuraEnemy.h"
#include "GAS/AuraAbilitySystemComponent.h"
#include "GAS/AuraAttributeSet.h"
#include "AuraBlueprintFunctionLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerController/AuraAiController.h"
#include "Tag/AuraGameplayTags.h"



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
	if(HasAuthority())
	{
		UAuraBlueprintFunctionLibrary::AddStartingAbilities(this , AbilityComponent,CharacterClass , Level);
	}

}

int32 AAuraEnemy::GetPlayerLevel_Implementation()
{
	return Level;
}

void AAuraEnemy::InitAttribute(UObject* Source)
{
	if(HasAuthority())
	{
		UAuraBlueprintFunctionLibrary::SetAttributeInfo(CharacterClass , this , AbilityComponent , Level);
	}

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

	/*
	 * 根据被打做出反应
	 */
	AbilityComponent->RegisterGameplayTagEvent(FAuraGameplayTags::Get().Effects_React , EGameplayTagEventType::NewOrRemoved).AddUObject(this ,&AAuraEnemy::ReactTagChange);
	
	OnHealthChanged.Broadcast(AuraSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraSet->GetMaxHealth());
}

void AAuraEnemy::PossessedBy(AController* NewController)
{
	
	if(!HasAuthority())return;
	Super::PossessedBy(NewController);
	
	AIController = Cast<AAuraAiController>(NewController);
	AIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset.Get());
	AIController->RunBehaviorTree(BehaviorTree);
	const bool IsRanegr = !(CharacterClass == ECharacterClass::Warrior);
	AIController->GetBlackboardComponent()->SetValueAsBool(FName("IsRanger") , IsRanegr);
}

void AAuraEnemy::ReactTagChange(const FGameplayTag Tag, int32 count)
{
	bHitReacting = count > 0 ;
	if(bHitReacting)
	{
		GetCharacterMovement()->StopActiveMovement();
		if(AIController)
		AIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReact") , true);

	}
	else
	{
		if(AIController)
			AIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReact"), false);
	}

	
}


void AAuraEnemy::HasDied_Implementation()
{
	DetachFromControllerPendingDestroy();
	Super::HasDied_Implementation();
	SetLifeSpan(LifeSpan);
}

AActor* AAuraEnemy::GetTargetActor_Implementation()
{
	return TargetEnemy;
}

void AAuraEnemy::SetTargetActor_Implementation(AActor* TargetActor)
{
	this->TargetEnemy = TargetActor;
}
