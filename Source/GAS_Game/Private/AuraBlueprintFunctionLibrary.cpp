// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraBlueprintFunctionLibrary.h"
#include "AuraUserWidgetController.h"
#include "AuraHUD.h"
#include "AuraAttributeSet.h"
#include "AuraGameModeBase.h"
#include "GameFramework/PlayerController.h"
#include "kismet/GameplayStatics.h"
#include "AuraPlayerState.h"

UOverlapWidgetController* UAuraBlueprintFunctionLibrary::GetOverlayWidgetController(UObject * WorldContext)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContext , 0))
	{
		AAuraPlayerState* PS = Cast<AAuraPlayerState>(PC->GetPlayerState<APlayerState>());
		UAbilitySystemComponent* Asc = PS->GetAbilitySystemComponent();
		UAttributeSet* As = PS->GetAttributeSet();
		const FWidgetContollerParams Wcp(PS, PC, Asc, As);
		if (AAuraHUD* HUD = Cast<AAuraHUD>(PC->GetHUD()))
			return HUD->GetOverlayWidgetController(Wcp);
	
		
	}

	return nullptr;
}

UAttributeWidgetController* UAuraBlueprintFunctionLibrary::GetAttributeWidgetController(UObject* WorldContext)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContext, 0))
	{
		AAuraPlayerState* PS = Cast<AAuraPlayerState>(PC->GetPlayerState<APlayerState>());


		UAbilitySystemComponent* Asc = PS->GetAbilitySystemComponent();
		UAttributeSet* As = PS->GetAttributeSet();
		const FWidgetContollerParams Wcp(PS, PC, Asc, As);
		if (AAuraHUD* HUD = Cast<AAuraHUD>(PC->GetHUD()))
			return HUD->GetAttributeWidgetController(Wcp);


	}
	return nullptr;
}


void UAuraBlueprintFunctionLibrary::SetAttributeInfo(ECharacterClass CharacterClass, UObject* WorldContext,
	UAbilitySystemComponent* AbilitySystemComponent , float Level)
{
	const AAuraGameModeBase * Gmb =  Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(WorldContext));
	if(!Gmb)return;
	
	const UCharacterDataInfo* DataInfo = Gmb->CharacterDataInfo.Get();
	check(DataInfo);
	

	
	const FCharacterDifDataInfo FDataInfo =  DataInfo->GetCharacterDataInfo(CharacterClass);

	 FGameplayEffectContextHandle GameContextHandle =  AbilitySystemComponent->MakeEffectContext();
	
	GameContextHandle.AddSourceObject(WorldContext);

	
	const FGameplayEffectSpecHandle PrimaryEffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(FDataInfo.PrimaryEffect ,Level,GameContextHandle); 
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*PrimaryEffectSpecHandle.Data.Get());

	const FGameplayEffectSpecHandle SecondaryEffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DataInfo->SecondaryEffet,Level ,GameContextHandle); 
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SecondaryEffectSpecHandle.Data.Get());

	const FGameplayEffectSpecHandle VitalEffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DataInfo->VitalEffet,Level ,GameContextHandle); 
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*VitalEffectSpecHandle.Data.Get());
}

void UAuraBlueprintFunctionLibrary::AddStartingAbilities(UObject * WorldContext , UAbilitySystemComponent* AbilitySystemComponent)
{
	const AAuraGameModeBase * Gmb =  Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(WorldContext));
	if(!Gmb)return;
	
	const UCharacterDataInfo* DataInfo = Gmb->CharacterDataInfo.Get();
	check(DataInfo);


	for(TSubclassOf<UGameplayAbility>GA : DataInfo->StartingAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(GA,1);
		AbilitySystemComponent->GiveAbility(AbilitySpec);
	}

}
