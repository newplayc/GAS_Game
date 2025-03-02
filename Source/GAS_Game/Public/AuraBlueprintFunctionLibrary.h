// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WidgetController/OverlapWidgetController.h"
#include "WidgetController/AttributeWidgetController.h"
#include "Data/CharacterDataInfo.h"
#include "Interface/ICombatInterface.h"
#include "WidgetController/SpellMenuWidgetController.h"
#include "AuraBlueprintFunctionLibrary.generated.h"

struct FEffectParams;


/**
 * 
 */
UCLASS()
class GAS_GAME_API UAuraBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION()
	static UAbilitiyInfo * GetAbilityInfo(const UObject * WorldContext);
	UFUNCTION()
	static bool GetUserControllerParams(const UObject * WorldContext , FWidgetContollerParams & WidgetContollerParams);
	UFUNCTION(BlueprintPure , BlueprintCallable ,meta=(DefaultToSelf="WorldContext"))
	static UOverlapWidgetController* GetOverlayWidgetController(const UObject * WorldContext);


	UFUNCTION(BlueprintPure, BlueprintCallable,meta=(DefaultToSelf="WorldContext"))
	static UAttributeWidgetController* GetAttributeWidgetController(const UObject* WorldContext);

	UFUNCTION(BlueprintPure, BlueprintCallable,meta=(DefaultToSelf="WorldContext"))
	static USpellMenuWidgetController* GetSpellMenuWidgetController(const UObject* WorldContext);

	
	UFUNCTION(BlueprintCallable)
	static void SetAttributeInfo(ECharacterClass  CharacterClass , const UObject* WorldContext , UAbilitySystemComponent* AbilitySystemComponent ,float Level);

	UFUNCTION(BlueprintCallable)
	static void AddStartingAbilities(UObject * WorldContext , UAbilitySystemComponent* AbilitySystemComponent ,ECharacterClass CharacterClass , int32 Level);

	UFUNCTION(BlueprintCallable)
	static UCurveTable * GetAttributeCurveTable(UObject * WorldContext);

	UFUNCTION(BlueprintCallable)
	static void SetGameContextBlock(  FGameplayEffectContextHandle& GameContextHandle , bool Block);

	UFUNCTION(BlueprintCallable)
	static void SetGameContextCritical(  FGameplayEffectContextHandle& GameContextHandle , bool Critical);

	UFUNCTION(BlueprintCallable , BlueprintPure)
	static bool GetGameContextBlock(const FGameplayEffectContextHandle& GameplayEffectContextHandle);

	UFUNCTION(BlueprintCallable , BlueprintPure)
	static bool GetGameContextCritical(const FGameplayEffectContextHandle& GameplayEffectContextHandle);

	UFUNCTION(BlueprintCallable)
	static void GetOverlapActors(const UObject* WorldContext , const FVector & Origin , const  TArray<AActor* > & Ignores ,const float Radius , TArray<AActor*> & HitActors);

	UFUNCTION(BlueprintCallable)
	static bool IsFriend(AActor * a1 , AActor* a2);

	UFUNCTION(BlueprintCallable)
	static  FTagMontage GetTagMontageWithTag(TArray<FTagMontage> TagMontages, const FGameplayTag& MontageTag);

	UFUNCTION(BlueprintCallable)
	static  TArray<FTagMontage> GetTagMontageTypeWithType(const TArray<FTagMontage>& TagMontages,const EAttackType& AttType);

	UFUNCTION(BlueprintCallable)
	static float GetCharacterExpValue(const UObject * WorldContext , ECharacterClass CharacterClass , int32 Level);

	static FActiveGameplayEffectHandle ApplyEffectParams(const FEffectParams & EffectParams);

	UFUNCTION(BlueprintCallable)
	static void SetEffectDebuffParamsContext(FGameplayEffectContextHandle & EffectContext, float Duration, float Frequency, float Damage, bool IsDebuff,const FGameplayTag
	                                         & DamageTypeTag);

	UFUNCTION(BlueprintCallable)
	static bool GetIsDebuffFromContext(const FGameplayEffectContextHandle & EffectContext);

	UFUNCTION(BlueprintCallable)
	static float GetDebuffDuration(const FGameplayEffectContextHandle & EffectContext);

	UFUNCTION(BlueprintCallable)
	static float GetDebuffFrequency(const FGameplayEffectContextHandle & EffectContext);

	UFUNCTION(BlueprintCallable)
	static float GetDebuffDamage(const FGameplayEffectContextHandle & EffectContext);

	UFUNCTION(BlueprintCallable)
	static FGameplayTag GetDamageTypeTag(const FGameplayEffectContextHandle & EffectContext);
};