// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/AuraCharacter.h"
#include "GAS/AuraAbilitySystemComponent.h"
#include "PlayerState/AuraPlayerState.h"
#include "PlayerController/AuraPlayerController.h"
#include "GAS/AuraAttributeSet.h"
#include "HUD/AuraHUD.h"

#include "GameFramework/CharacterMovementComponent.h"


AAuraCharacter::AAuraCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 400.0, 0);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	
	
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
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	IniAbilityInfo();

}


int32 AAuraCharacter::GetPlayerLevel()
{
	AAuraPlayerState* PS = GetPlayerState<AAuraPlayerState>();
	if (!PS)return -1;
	return PS->GetPlayerLevel();
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
}

