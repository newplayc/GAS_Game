// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraBlueprintFunctionLibrary.h"
#include "AuraUserWidgetController.h"
#include "AuraHUD.h"
#include "GameFramework/PlayerController.h"
#include "kismet/GameplayStatics.h"
#include "AuraPlayerState.h"

UOverlapWidgetController* UAuraBlueprintFunctionLibrary::GetOverlayWidgetController(UObject * WorldContext)
{

	APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContext , 0);
	if (PC)
	{
		AAuraPlayerState* PS = Cast<AAuraPlayerState>(PC->GetPlayerState<APlayerState>());

		
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			FWidgetContollerParams WCP(PS, PC, ASC, AS);
			AAuraHUD* HUD = Cast<AAuraHUD>(PC->GetHUD());
			if (HUD)
				return HUD->GetOverlayWidgetController(WCP);
	
		
	}

	return nullptr;
}

UAttributeWidgetController* UAuraBlueprintFunctionLibrary::GetAttributeWidgetController(UObject* WorldContext)
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContext, 0);
	if (PC)
	{
		AAuraPlayerState* PS = Cast<AAuraPlayerState>(PC->GetPlayerState<APlayerState>());


		UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
		UAttributeSet* AS = PS->GetAttributeSet();
		FWidgetContollerParams WCP(PS, PC, ASC, AS);
		AAuraHUD* HUD = Cast<AAuraHUD>(PC->GetHUD());
		if (HUD)
			return HUD->GetAttributeWidgetController(WCP);


	}
	return nullptr;
}
