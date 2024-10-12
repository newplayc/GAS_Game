// Fill out your copyright notice in the Description page of Project Settings.

#include "AuraCharacter.h"
#include "AuraAbilitySystemComponent.h"
#include "AuraPlayerState.h"
#include "AuraPlayerController.h"
#include "AuraAttributeSet.h"
#include "AuraHUD.h"
#include "GameFramework/CharacterMovementComponent.h"


AAuraCharacter::AAuraCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 400.0, 0);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;


}



UAbilitySystemComponent* AAuraCharacter::GetAbilitySystemComponent() const
{
	AAuraPlayerState* PS = GetPlayerState<AAuraPlayerState>();
	check(PS)

	return PS->GetAbilitySystemComponent();
	
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	IniAbilityInfo();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	IniAbilityInfo();

}


int32 AAuraCharacter::GetPlayerLevel()
{
	AAuraPlayerState* PS = GetPlayerState<AAuraPlayerState>();
	check(PS);
	return PS->GetPlayerLevel();
}


void AAuraCharacter::IniAbilityInfo()
{

	AAuraPlayerState* PS = GetPlayerState<AAuraPlayerState>();
	check(PS);
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
	ASC->InitAttribute(this);
	
}

