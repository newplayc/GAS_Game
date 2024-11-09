// Fill out your copyright notice in the Description page of Project Settings.


#include "Calculation/ExeCalDamage.h"

#include "AuraBlueprintFunctionLibrary.h"
#include "FileCache.h"
#include "Tag/AuraGameplayTags.h"
#include "Interface/ICombatInterface.h"
#include "GAS/Effect/AuraGameplayEffectTypes.h"


UExeCalDamage::UExeCalDamage()
{
	RelevantAttributesToCapture.Add(GetDefinitionStatic().ArmorDef);
	RelevantAttributesToCapture.Add(GetDefinitionStatic().ArmorPenetrationDef);
	RelevantAttributesToCapture.Add(GetDefinitionStatic().BlockChanceDef);
	RelevantAttributesToCapture.Add(GetDefinitionStatic().CriticalHitChanceDef);
	RelevantAttributesToCapture.Add(GetDefinitionStatic().CriticalHitResistanceDef);
}


void UExeCalDamage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	
	const FGameplayEffectSpec Effectspec = ExecutionParams.GetOwningSpec();
	const UAbilitySystemComponent *  SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent * TargetASC =   ExecutionParams.GetTargetAbilitySystemComponent();
	 FGameplayEffectContextHandle EffectContextHandle = Effectspec.GetContext();
	 IICombatInterface * SourceCom = Cast<IICombatInterface>(SourceASC->GetAvatarActor());
	 IICombatInterface * TargetCom = Cast<IICombatInterface>(TargetASC->GetAvatarActor());
	const FGameplayTagContainer * SourceTags =   Effectspec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer * TargetTags =   Effectspec.CapturedTargetTags.GetAggregatedTags();
	
	FAggregatorEvaluateParameters AggregatorParameters;
	AggregatorParameters.SourceTags = SourceTags;
	AggregatorParameters.TargetTags = TargetTags;

	
	UCurveTable * AttCt = UAuraBlueprintFunctionLibrary::GetAttributeCurveTable(SourceASC->GetAvatarActor());
	
	float TargetArmor = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDefinitionStatic().ArmorDef ,AggregatorParameters, TargetArmor);

	float SourceArmorPenetration = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDefinitionStatic().ArmorPenetrationDef , AggregatorParameters , SourceArmorPenetration);

	float TargetBlockChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDefinitionStatic().BlockChanceDef , AggregatorParameters , TargetBlockChance);

	float SourceCriticalHitChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDefinitionStatic().CriticalHitChanceDef ,AggregatorParameters , SourceCriticalHitChance);

	float TargetCriticalHitResistance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDefinitionStatic().CriticalHitResistanceDef , AggregatorParameters , TargetCriticalHitResistance);

	SourceCriticalHitChance = SourceCriticalHitChance * (100 - TargetCriticalHitResistance * 0.25) /100.f;

	
	FRealCurve * ArPenCurve = AttCt->FindCurve("ArmorPenetration" , FString());
	float EffArmor = TargetArmor  * (100 - SourceArmorPenetration * ArPenCurve->Eval(SourceCom->GetPlayerLevel())) / 100.f;
	
	const float Damage  = Effectspec.GetSetByCallerMagnitude(FAuraGameplayTags::Get().Damage);
	const bool bCritical = FMath::RandRange(0 , 100)<=SourceCriticalHitChance;
	FRealCurve * ArCurve = AttCt->FindCurve("Armor" , FString());
	
	const float ArmorCoeffient = ArCurve->Eval(TargetCom->GetPlayerLevel());
	float EffDamage  = bCritical ? Damage * 2 * (100 - EffArmor * ArmorCoeffient) / 100.f:Damage * (100 - EffArmor * ArmorCoeffient) / 100.f;
	
	const bool bBlock = FMath::RandRange(0 , 100) <= TargetBlockChance;
	EffDamage = bBlock ? EffDamage / 2 : EffDamage;
	
	UAuraBlueprintFunctionLibrary::SetGameContextBlock( EffectContextHandle, bBlock);
	
	UAuraBlueprintFunctionLibrary::SetGameContextCritical( EffectContextHandle, bCritical);
	
	FGameplayModifierEvaluatedData EffData = FGameplayModifierEvaluatedData(UAuraAttributeSet::GetIncomingDamageAttribute() ,EGameplayModOp::Override , EffDamage);
	
	OutExecutionOutput.AddOutputModifier(EffData);
}
