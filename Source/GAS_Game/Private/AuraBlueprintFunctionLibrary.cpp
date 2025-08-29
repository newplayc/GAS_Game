// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraBlueprintFunctionLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Character/AuraCharacterBase.h"
#include "Engine/OverlapResult.h"
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



UAbilitiyInfo* UAuraBlueprintFunctionLibrary::GetAbilityInfo(const UObject* WorldContext)
{
	if(UOverlapWidgetController * OverlayController = GetOverlayWidgetController(WorldContext))
	{
		return OverlayController->AbilityInfos;
	}
	return nullptr;
}

bool UAuraBlueprintFunctionLibrary::GetUserControllerParams(const UObject* WorldContext ,FWidgetContollerParams & WidgetContollerParams)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContext , 0))
	{
		AAuraPlayerState* PS = Cast<AAuraPlayerState>(PC->GetPlayerState<APlayerState>());
		UAbilitySystemComponent* Asc = PS->GetAbilitySystemComponent();
		UAttributeSet* As = PS->GetAttributeSet();
		WidgetContollerParams.SetParams(PS , PC , Asc ,As);
		return true;
	}
	return false;
}

UOverlapWidgetController* UAuraBlueprintFunctionLibrary::GetOverlayWidgetController(const UObject * WorldContext)
{
	FWidgetContollerParams WidgetControllerParams;
	if(GetUserControllerParams(WorldContext , WidgetControllerParams))
	{
		return Cast<AAuraHUD>(WidgetControllerParams.PlayerController->GetHUD())->GetOverlayWidgetController(WidgetControllerParams);
	}
	return nullptr;
}

UAttributeWidgetController* UAuraBlueprintFunctionLibrary::GetAttributeWidgetController(const UObject* WorldContext)
{
	FWidgetContollerParams WidgetControllerParams;
	if(GetUserControllerParams(WorldContext , WidgetControllerParams))
	{
		return Cast<AAuraHUD>(WidgetControllerParams.PlayerController->GetHUD())->GetAttributeWidgetController(WidgetControllerParams);
	}
	return nullptr;
}

USpellMenuWidgetController* UAuraBlueprintFunctionLibrary::GetSpellMenuWidgetController(const UObject* WorldContext)
{
	FWidgetContollerParams WidgetControllerParams;
	if(GetUserControllerParams(WorldContext , WidgetControllerParams))
	{
		return Cast<AAuraHUD>(WidgetControllerParams.PlayerController->GetHUD())->GetSpellMenuWidgetController(WidgetControllerParams);
	}
	return nullptr;
}


void UAuraBlueprintFunctionLibrary::SetAttributeInfo(ECharacterClass CharacterClass,const  UObject* WorldContext,
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
		if(res.GetActor()->Implements<UICombatInterface>() && !IICombatInterface::Execute_IsDead(res.GetActor()))
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
	for( const FTagMontage& It : TagMontages)
	{
		if(It.AttType == AttType)
		{
			TypeMontage.AddUnique(It);
		}
	}
	return TypeMontage;
}

float UAuraBlueprintFunctionLibrary::GetCharacterExpValue(const UObject* WorldContext, ECharacterClass CharacterClass,
	int32 Level)
{
	AAuraGameModeBase * GM  = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(WorldContext));
	if(!IsValid(GM))return 0.f;
	
	const UCharacterDataInfo* DataInfo = GM->CharacterDataInfo.Get();
	check(DataInfo);
	
	return DataInfo->GetCharacterDataInfo(CharacterClass).ExpValue.GetValueAtLevel(Level);
}

FActiveGameplayEffectHandle UAuraBlueprintFunctionLibrary::ApplyEffectParams(const FEffectParams& EffectParams)
{
	
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(EffectParams.EffectSpecHandle ,EffectParams.DamageTypeTag , EffectParams.BaseDamage);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(EffectParams.EffectSpecHandle,FAuraGameplayTags::Get().Debuff_Damage, EffectParams.DebuffDamage);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(EffectParams.EffectSpecHandle,FAuraGameplayTags::Get().Debuff_Chance, EffectParams.DebuffChance);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(EffectParams.EffectSpecHandle,FAuraGameplayTags::Get().Debuff_Duration, EffectParams.DebuffDuration);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(EffectParams.EffectSpecHandle,FAuraGameplayTags::Get().Debuff_Frequency, EffectParams.DebuffFrequency);

	SetDeathImpluse(EffectParams.EffectSpecHandle.Data.Get()->GetContext(), EffectParams.DeathImpulseDirection);
	SetKnockBack(EffectParams.EffectSpecHandle.Data.Get()->GetContext() , EffectParams.KnockBackDirection);
	
	FActiveGameplayEffectHandle ActiveGameplayEffectHandle =  EffectParams.SourceAbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*(EffectParams.EffectSpecHandle.Data.Get()) , EffectParams.TargetAbilitySystemComponent);
	return ActiveGameplayEffectHandle;
}

void UAuraBlueprintFunctionLibrary::SetEffectDebuffParamsContext(FGameplayEffectContextHandle& EffectContextHandle, float Duration,
                                                                 float Frequency, float Damage, bool IsDebuff, const FGameplayTag& DamageTypeTag)
{
	if(FAuraGameplayEffectContext * GEC = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		
		GEC->SetDebuffDamage(Damage);
		GEC->SetIsDebuff(IsDebuff);
		GEC->SetDebuffFrequency(Frequency);
		GEC->SetDebuffDuration(Duration);
		GEC->SetDamageTypeTag(MakeShareable(new FGameplayTag(DamageTypeTag)));
	}
}

bool UAuraBlueprintFunctionLibrary::GetIsDebuffFromContext(const FGameplayEffectContextHandle& EffectContext)
{
	if(const FAuraGameplayEffectContext * GEC = static_cast<const FAuraGameplayEffectContext*>(EffectContext.Get()))
	{
		return GEC->GetIsDebuff();
	}
	return false;
}

float UAuraBlueprintFunctionLibrary::GetDebuffDuration(const FGameplayEffectContextHandle& EffectContext)
{
	if(const FAuraGameplayEffectContext * GEC = static_cast<const FAuraGameplayEffectContext*>(EffectContext.Get()))
	{
		return GEC->GetDebuffDuration();
	}
		return 0.f;
}

float UAuraBlueprintFunctionLibrary::GetDebuffFrequency(const FGameplayEffectContextHandle& EffectContext)
{
	if(const FAuraGameplayEffectContext * GEC = static_cast<const FAuraGameplayEffectContext*>(EffectContext.Get()))
	{
		return GEC->GetDebuffFrequency();
	}
	return 0.f;
}

float UAuraBlueprintFunctionLibrary::GetDebuffDamage(const FGameplayEffectContextHandle& EffectContext)
{
	if(const FAuraGameplayEffectContext * GEC = static_cast<const FAuraGameplayEffectContext*>(EffectContext.Get()))
	{
		return GEC->GetDebuffDamage();
	}
	return 0.f;
}

FGameplayTag UAuraBlueprintFunctionLibrary::GetDamageTypeTag(const FGameplayEffectContextHandle& EffectContext)
{
	if(const FAuraGameplayEffectContext * GEC = static_cast<const FAuraGameplayEffectContext*>(EffectContext.Get()))
	{
		return GEC->GetDamageTypeTag();
	}
	return FGameplayTag();
}

void UAuraBlueprintFunctionLibrary::SetDeathImpluse( FGameplayEffectContextHandle EffectContext,
	const FVector &  InFVector)
{
	if( FAuraGameplayEffectContext * GEC = static_cast< FAuraGameplayEffectContext*>(EffectContext.Get()))
	{
		return GEC->SetDeathDirection(InFVector);
	}
}

FVector UAuraBlueprintFunctionLibrary::GetDeathImpluse(const FGameplayEffectContextHandle& EffectContextHandle) 
{
	if(const  FAuraGameplayEffectContext * GEC = static_cast< const FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return GEC->GetDeathVector();
	}
	return FVector();
}

void UAuraBlueprintFunctionLibrary::SetKnockBack(FGameplayEffectContextHandle EffectContextHandle,
	const FVector& InFVector)
{
	if( FAuraGameplayEffectContext * GEC = static_cast< FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return GEC->SetKnockBackDirection(InFVector);
	}
}

FVector UAuraBlueprintFunctionLibrary::GetKnockBack(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if(const  FAuraGameplayEffectContext * GEC = static_cast< const FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return GEC->GetKnockBackDirection();
	}
	return FVector();
}

void UAuraBlueprintFunctionLibrary::SetLifeSiphon( FGameplayEffectContextHandle& EffectContextHandle, float Life)
{
	if( FAuraGameplayEffectContext * GEC = static_cast< FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		GEC->SetLifeSiphon(Life);
	}
}

void UAuraBlueprintFunctionLibrary::SetManaSiphon( FGameplayEffectContextHandle& EffectContextHandle, float Mana)
{
	if( FAuraGameplayEffectContext * GEC = static_cast< FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		GEC->SetManaSiphon(Mana);
	}
}

float UAuraBlueprintFunctionLibrary::GetLifeSiphon(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if(const  FAuraGameplayEffectContext * GEC = static_cast< const FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return GEC->GetLifeSiphon();
	}
	return 0.f;
}

float UAuraBlueprintFunctionLibrary::GetManaSiphon(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if(const  FAuraGameplayEffectContext * GEC = static_cast< const FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return GEC->GetManaSiphon();
	}
	return 0.f;
}



