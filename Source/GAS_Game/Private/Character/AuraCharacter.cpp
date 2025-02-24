// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/AuraCharacter.h"


#include "GAS/AuraAbilitySystemComponent.h"
#include "PlayerState/AuraPlayerState.h"
#include "PlayerController/AuraPlayerController.h"
#include "GAS/AuraAttributeSet.h"
#include "HUD/AuraHUD.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NiagaraComponent.h"
#include "Components/AudioComponent.h"


AAuraCharacter::AAuraCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 400.0, 0);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	LevelUpNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("LevelUpNiagara");
	LevelUpNiagaraComponent->bAutoActivate = false;
	LevelUpNiagaraComponent->SetupAttachment(RootComponent);
	LevelUpAudioComponent = CreateDefaultSubobject<UAudioComponent>("LevelUpAudioCom");
	LevelUpAudioComponent->bAutoActivate = false;
	LevelUpAudioComponent->SetupAttachment(RootComponent);
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}



UAbilitySystemComponent* AAuraCharacter::GetAbilitySystemComponent() const
{
	AAuraPlayerState* PS = GetPlayerState<AAuraPlayerState>();
	if (!PS)return nullptr;
	return PS->GetAbilitySystemComponent();
	
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	IniAbilityInfo();
	GiveStartAbilities();
	GetPlayerState<AAuraPlayerState>()->InitXpAndLevel();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	IniAbilityInfo();
}


int32 AAuraCharacter::GetPlayerLevel_Implementation()
{
	if(AAuraPlayerState * Ps = CastChecked<AAuraPlayerState>(GetPlayerState()))
	{
		return Ps->GetPlayerLevel();
	}
	return 0;
}

void AAuraCharacter::SetLevel_Implementation(int InLevel)
{
	if(AAuraPlayerState * Ps = CastChecked<AAuraPlayerState>(GetPlayerState()))
	{
		Ps->SetLevel(InLevel);
	}
	
}

void AAuraCharacter::SetExp_Implementation(float InExp)
{
	if(AAuraPlayerState * Ps = CastChecked<AAuraPlayerState>(GetPlayerState()))
	{
		Ps->SetExp(InExp);
	}
}

void AAuraCharacter::AddExp_Implementation(float InExp)
{
	if(AAuraPlayerState * Ps = CastChecked<AAuraPlayerState>(GetPlayerState()))
	{
		Ps->AddExp(InExp);
	}
}

void AAuraCharacter::AddLevel_Implementation(int InLevel)
{
	if(AAuraPlayerState * Ps = CastChecked<AAuraPlayerState>(GetPlayerState()))
	{
		Ps->AddLevel(InLevel);
	}
	
}

int32 AAuraCharacter::GetExp_Implementation()
{
	if(AAuraPlayerState * Ps = CastChecked<AAuraPlayerState>(GetPlayerState()))
	{
		return Ps->GetExp();
	}
	return 0;
}

int32 AAuraCharacter::GetSpellPoints_Implementation()
{
	if(AAuraPlayerState * Ps = CastChecked<AAuraPlayerState>(GetPlayerState()))
	{
		return Ps->GetSpellPoints();
	}
	return 0;
}

int32 AAuraCharacter::GetTalentPoints_Implementation()
{
	if(AAuraPlayerState * Ps = CastChecked<AAuraPlayerState>(GetPlayerState()))
	{
		 return Ps->GetTalentPoints();
	}
	return 0;
}

void AAuraCharacter::AddSpellPoints_Implementation(int32 InPoints)
{
	if(AAuraPlayerState * Ps = CastChecked<AAuraPlayerState>(GetPlayerState()))
	{
		Ps->AddSpellPoints(InPoints);
	}
}

void AAuraCharacter::AddTalentPoints_Implementation(int32 InPoints)
{
	if(AAuraPlayerState * Ps = CastChecked<AAuraPlayerState>(GetPlayerState()))
	{
		Ps->AddTalentPoints(InPoints);
	}
}

void AAuraCharacter::AddPointsAfterInitAttribute(UObject * Source)
{
	AbilityComponent->ApplyEffectToInit(InitalSecondaryEffect, GetPlayerLevel_Implementation() , Source);
	AbilityComponent->ApplyEffectToInit(InitalVitalEffect,GetPlayerLevel_Implementation()  ,Source);
}

void AAuraCharacter::Level_up_Implementation()
{
	PlayLevelEffect();
	AddPointsAfterInitAttribute(this);
}


void AAuraCharacter::PlayLevelEffect_Implementation()
{
	LevelUpNiagaraComponent->Activate(true);
	LevelUpAudioComponent->Activate(true);
}


void AAuraCharacter::IniAbilityInfo()
{

	AAuraPlayerState* PS = GetPlayerState<AAuraPlayerState>();
	
	if (!PS)return;
	UAuraAbilitySystemComponent* ASC = Cast<UAuraAbilitySystemComponent>(PS->GetAbilitySystemComponent());
	check(ASC);
	AbilityComponent = ASC;
	ASC->InitAbilityActorInfo(PS, this);

	UAuraAttributeSet* AS = PS->GetAttributeSet();
	AttributeSet = AS;
	AAuraPlayerController* PlayerController = Cast<AAuraPlayerController>(GetController());
	if (PlayerController)
	{
		if (AAuraHUD* AHUD = Cast<AAuraHUD>(PlayerController->GetHUD()))
		{
			AHUD->IniOverlayWidget(PS, PlayerController, ASC, AS);
		}
	}
	
	InitAttribute(this);
	
}

void AAuraCharacter::GiveStartAbilities()
{
	UAuraAbilitySystemComponent* ASC = Cast<UAuraAbilitySystemComponent>(AbilityComponent);
	ASC->GiveAbilitiesArray(StartAbilitys);
	ASC->GiveBaseAbilitiesArray(BaseAbilitys);

}
