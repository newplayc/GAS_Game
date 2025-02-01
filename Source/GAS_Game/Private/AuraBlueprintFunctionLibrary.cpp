// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraBlueprintFunctionLibrary.h"

#include "Character/AuraCharacterBase.h"
#include "WidgetController/AuraUserWidgetController.h"
#include "HUD/AuraHUD.h"
#include "GAS/AuraAttributeSet.h"
#include "Game/AuraGameModeBase.h"
#include "GameFramework/PlayerController.h"
#include "GAS/Ability/AuraGameplayAbility.h"
#include "GAS/Effect/AuraGameplayEffectTypes.h"
#include "Interface/ICombatInterface.h"
#include "kismet/GameplayStatics.h"
#include "PlayerState/AuraPlayerState.h"
#include "Tag/AuraGameplayTags.h"

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

void UAuraBlueprintFunctionLibrary::AddStartingAbilities(UObject * WorldContext , UAbilitySystemComponent* AbilitySystemComponent , ECharacterClass CharacterClass , int32 Level)
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

	const FCharacterDifDataInfo FDataInfo =  DataInfo->GetCharacterDataInfo(CharacterClass);
	for(TSubclassOf<UGameplayAbility> Ability : FDataInfo.StartingAbilities)
	{
		FGameplayAbilitySpec Aspec = FGameplayAbilitySpec(Ability ,Level);
		AbilitySystemComponent->GiveAbility(Aspec);
	}

}

UCurveTable* UAuraBlueprintFunctionLibrary::GetAttributeCurveTable(UObject* WorldContext)
{
	const AAuraGameModeBase * Gmb =  Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(WorldContext));
	if(!Gmb)return nullptr;

	return Gmb->CharacterDataInfo->AttributeCurve;
	
}

void UAuraBlueprintFunctionLibrary::SetGameContextBlock( FGameplayEffectContextHandle& GameContextHandle, bool Block)
{
	if( FAuraGameplayEffectContext * GEC = static_cast<FAuraGameplayEffectContext*>(GameContextHandle.Get()))
	{
		GEC->SetbBlock(Block);
	}
}

void UAuraBlueprintFunctionLibrary::SetGameContextCritical( FGameplayEffectContextHandle& GameContextHandle,
	bool Critical)
{
	if( FAuraGameplayEffectContext * GEC = static_cast<FAuraGameplayEffectContext*>(GameContextHandle.Get()))
	{
    		GEC->SetbCritical(Critical);
	}
}

bool UAuraBlueprintFunctionLibrary::GetGameContextBlock(const FGameplayEffectContextHandle& GameplayEffectContextHandle)
{
	if( const FAuraGameplayEffectContext * GEC = static_cast<const FAuraGameplayEffectContext*>(GameplayEffectContextHandle.Get()))
	{
		return GEC->GetbBlock();
	}
	return false;
}

bool UAuraBlueprintFunctionLibrary::GetGameContextCritical(
	const FGameplayEffectContextHandle& GameplayEffectContextHandle)
{
	if( const FAuraGameplayEffectContext * GEC = static_cast<const FAuraGameplayEffectContext*>(GameplayEffectContextHandle.Get()))
	{
		return GEC->GetbCritical();
	}
	return false;
}

void  UAuraBlueprintFunctionLibrary::GetOverlapActors(const UObject* WorldContext, const FVector& Origin,
	const TArray<AActor*>& Ignores , const float Radius , TArray<AActor*> & HitActors)
{
	FCollisionQueryParams SphereParams;
	SphereParams.AddIgnoredActors(Ignores);


	TArray<FOverlapResult> Overlaps;
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::LogAndReturnNull))
	{
		World->OverlapMultiByObjectType(Overlaps, Origin, FQuat::Identity, FCollisionObjectQueryParams(FCollisionObjectQueryParams::InitType::AllDynamicObjects), FCollisionShape::MakeSphere(Radius), SphereParams);
	}
	
	for(FOverlapResult& res : Overlaps)
	{
		if(res.GetActor()->Implements<UICombatInterface>() && !(IICombatInterface::Execute_IsDead(res.GetActor())))
		{
			HitActors.AddUnique(res.GetActor());
		}
	}
}

bool UAuraBlueprintFunctionLibrary::IsFriend(AActor* a1, AActor* a2)
{
	if(a1->ActorHasTag(FName("player")))
	{
		return a2->ActorHasTag(FName("player"));
	}
	else
	{
		return a2->ActorHasTag(FName("Enemy"));
	}
}

 FTagMontage UAuraBlueprintFunctionLibrary::GetTagMontageWithTag( TArray<FTagMontage> TagMontages, const FGameplayTag& MontageTag)
{
	for(auto TagMon : TagMontages)
	{
		if(TagMon.MontageTag.MatchesTagExact(MontageTag))
		{
			return TagMon;
		}
	}
	return FTagMontage();
}

 TArray< FTagMontage> UAuraBlueprintFunctionLibrary::GetTagMontageTypeWithType( const TArray<FTagMontage>& TagMontages,
const EAttackType & AttType)
{
	TArray<FTagMontage>TypeMontage;
	for( const FTagMontage& it : TagMontages)
	{
		if(it.AttType == AttType)
		{
			TypeMontage.AddUnique(it);
		}
	}
	return TypeMontage;
}
