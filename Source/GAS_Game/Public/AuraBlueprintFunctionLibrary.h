// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WidgetController/OverlapWidgetController.h"
#include "WidgetController/AttributeWidgetController.h"
#include "Data/CharacterDataInfo.h"
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
};