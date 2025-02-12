// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WidgetController/OverlapWidgetController.h"
#include "WidgetController/AttributeWidgetController.h"
#include "Data/CharacterDataInfo.h"
#include "Interface/ICombatInterface.h"
#include "AuraBlueprintFunctionLibrary.generated.h"



/**
 * 
 */
UCLASS()
class GAS_GAME_API UAuraBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure , BlueprintCallable)
	static UOverlapWidgetController* GetOverlayWidgetController(UObject * WorldContext);


	UFUNCTION(BlueprintPure, BlueprintCallable)
	static UAttributeWidgetController* GetAttributeWidgetController(UObject* WorldContext);

	UFUNCTION(BlueprintCallable)
	static void SetAttributeInfo(ECharacterClass  CharacterClass , UObject* WorldContext , UAbilitySystemComponent* AbilitySystemComponent ,float Level);

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

	UFUNCTION(BlueprintCallable)
	static float GetExpPercent(const UObject* WorldContext , int32 Level , float NowExp);

	UFUNCTION(BlueprintCallable)
	static TArray<float> GetExpFloat(const UObject* WorldContext , int32 Level);
};