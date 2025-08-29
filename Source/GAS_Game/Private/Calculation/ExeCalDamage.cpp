// Fill out your copyright notice in the Description page of Project Settings.


#include "Calculation/ExeCalDamage.h"


#include "AuraBlueprintFunctionLibrary.h"
#include "GAS/AuraAttributeSet.h"
#include "Tag/AuraGameplayTags.h"
#include "Interface/ICombatInterface.h"
#include "GAS/Effect/AuraGameplayEffectTypes.h"

USTRUCT()
struct FCaptureDefinitionStatic
{

	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitResistance);

	DECLARE_ATTRIBUTE_CAPTUREDEF(FireResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArcaneResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(LightningResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicsResistance);

	DECLARE_ATTRIBUTE_CAPTUREDEF(LifeSiphon);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ManaSiphon);
	
	FCaptureDefinitionStatic()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, ArmorPenetration , Source , false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Armor , Target , false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, BlockChance , Target , false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CriticalHitChance , Source , false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CriticalHitResistance , Target , false);
		
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, FireResistance , Target , false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, ArcaneResistance , Target , false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, LightningResistance , Target , false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, PhysicsResistance , Target , false);

		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet , LifeSiphon ,Source , false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet , ManaSiphon ,Source , false);
	}
	
};


static const FCaptureDefinitionStatic& GetDefinitionStatic()
{
	static FCaptureDefinitionStatic captureDefinitionStatic;
	return captureDefinitionStatic;
}



UExeCalDamage::UExeCalDamage()
{
	RelevantAttributesToCapture.Add(GetDefinitionStatic().ArmorDef);
	RelevantAttributesToCapture.Add(GetDefinitionStatic().ArmorPenetrationDef);
	RelevantAttributesToCapture.Add(GetDefinitionStatic().BlockChanceDef);
	RelevantAttributesToCapture.Add(GetDefinitionStatic().CriticalHitChanceDef);
	RelevantAttributesToCapture.Add(GetDefinitionStatic().CriticalHitResistanceDef);
	
	RelevantAttributesToCapture.Add(GetDefinitionStatic().ArcaneResistanceDef);
	RelevantAttributesToCapture.Add(GetDefinitionStatic().FireResistanceDef);
	RelevantAttributesToCapture.Add(GetDefinitionStatic().LightningResistanceDef);
	RelevantAttributesToCapture.Add(GetDefinitionStatic().PhysicsResistanceDef);

	RelevantAttributesToCapture.Add(GetDefinitionStatic().LifeSiphonDef);
	RelevantAttributesToCapture.Add(GetDefinitionStatic().ManaSiphonDef);
}


void UExeCalDamage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	
	TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition> AttributeDefinitions;
	const FAuraGameplayTags & AuraGameplayTags = FAuraGameplayTags::Get();
		
	AttributeDefinitions.Add(AuraGameplayTags.Attributes_Secondary_Armor , GetDefinitionStatic().ArmorDef);
	AttributeDefinitions.Add(AuraGameplayTags.Attributes_Secondary_ArmorPenetration , GetDefinitionStatic().ArmorPenetrationDef);
	AttributeDefinitions.Add(AuraGameplayTags.Attributes_Secondary_BlockChance , GetDefinitionStatic().BlockChanceDef);
	AttributeDefinitions.Add(AuraGameplayTags.Attributes_Secondary_CriticalHitChance , GetDefinitionStatic().CriticalHitChanceDef);
	AttributeDefinitions.Add(AuraGameplayTags.Attributes_Secondary_CriticalHitResistance , GetDefinitionStatic().CriticalHitResistanceDef);

	
	/* 抵御类型  */
	AttributeDefinitions.Add(AuraGameplayTags.Attributes_Resistance_FireResistance , GetDefinitionStatic().FireResistanceDef);
	AttributeDefinitions.Add(AuraGameplayTags.Attributes_Resistance_ArcaneResistance , GetDefinitionStatic().ArcaneResistanceDef);
	AttributeDefinitions.Add(AuraGameplayTags.Attributes_Resistance_LightningResistance ,GetDefinitionStatic().LightningResistanceDef);
	AttributeDefinitions.Add(AuraGameplayTags.Attributes_Resistance_PhysicsResistance ,GetDefinitionStatic().PhysicsResistanceDef);

	
	const FGameplayEffectSpec Effectspec = ExecutionParams.GetOwningSpec();
	
	const UAbilitySystemComponent *  SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent * TargetASC =   ExecutionParams.GetTargetAbilitySystemComponent();
	FGameplayEffectContextHandle EffectContextHandle = Effectspec.GetContext();
	AActor * SourceActor = SourceASC->GetAvatarActor();
	AActor * TargetActor = TargetASC->GetAvatarActor();
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

	FAuraGameplayTags Tags = FAuraGameplayTags::Get();
	

	//计算伤害  抵御掉的伤害
	float Damage  = 0;
	for(auto Data : Tags.DamageTypeToResistance)
	{
		// Debuff
		float DebuffDamage = Effectspec.GetSetByCallerMagnitude(Tags.Debuff_Damage , false);
		float DebuffDuration = Effectspec.GetSetByCallerMagnitude(Tags.Debuff_Duration, false);
		float DebuffFrequency = Effectspec.GetSetByCallerMagnitude(Tags.Debuff_Frequency, false);
		float DebuffChance = Effectspec.GetSetByCallerMagnitude(Tags.Debuff_Chance, false);

		
		const FGameplayTag DamageType =  Data.Key;
		const FGameplayTag DamageResistance =  Data.Value;
		float DamageTypeValue  = Effectspec.GetSetByCallerMagnitude(DamageType , false);

		checkf(AttributeDefinitions.Contains(DamageResistance) , TEXT("TagsCapture Not Found %s"),*DamageResistance.ToString());
		const FGameplayEffectAttributeCaptureDefinition CaptureDefinition = AttributeDefinitions[DamageResistance];
		
		float DamageResistanceValue  = 0.f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(CaptureDefinition, AggregatorParameters , DamageResistanceValue);
		DamageResistanceValue  = FMath::Clamp(DamageResistanceValue, 0.f, 100.f);

		if(DamageTypeValue > 0.5f) //Debuff
		{
			DebuffChance = DebuffChance*  (100- DamageResistanceValue)/ 100;
			const bool bDebuff = FMath::RandRange(0 , 100) <= DebuffChance;
			UAuraBlueprintFunctionLibrary::SetEffectDebuffParamsContext(EffectContextHandle , DebuffDuration ,DebuffFrequency ,DebuffDamage ,bDebuff,DamageType);
		}
		
		DamageTypeValue = DamageTypeValue * (100 - DamageResistanceValue) / 100.f;
	
		Damage += DamageTypeValue;
	}
	

	
	SourceCriticalHitChance = SourceCriticalHitChance * (100 - TargetCriticalHitResistance * 0.25) /100.f;
	
	FRealCurve * ArPenCurve = AttCt->FindCurve("ArmorPenetration" , FString());
	float EffArmor = TargetArmor  * (100 - SourceArmorPenetration * ArPenCurve->Eval(IICombatInterface::Execute_GetPlayerLevel(SourceActor))) / 100.f;
	
	const bool bCritical = FMath::RandRange(0 , 100)<=SourceCriticalHitChance;
	
	FRealCurve * ArCurve = AttCt->FindCurve("Armor" , FString());
	
	const float ArmorCoeffient = ArCurve->Eval(IICombatInterface::Execute_GetPlayerLevel(TargetActor));
	float EffDamage  = bCritical ? Damage * 2 * (100 - EffArmor * ArmorCoeffient) / 100.f:Damage * (100 - EffArmor * ArmorCoeffient) / 100.f;
	
	const bool bBlock = FMath::RandRange(0 , 100) <= TargetBlockChance;
	EffDamage = bBlock ? EffDamage / 2 : EffDamage;
	
	UAuraBlueprintFunctionLibrary::SetGameContextBlock( EffectContextHandle, bBlock);
	
	UAuraBlueprintFunctionLibrary::SetGameContextCritical( EffectContextHandle, bCritical);
	
	float LifeSiphon = 0.f;
	float ManaSiphon = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDefinitionStatic().LifeSiphonDef ,AggregatorParameters, LifeSiphon);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDefinitionStatic().ManaSiphonDef ,AggregatorParameters, ManaSiphon);
	
	UAuraBlueprintFunctionLibrary::SetLifeSiphon(EffectContextHandle , LifeSiphon);
	UAuraBlueprintFunctionLibrary::SetManaSiphon(EffectContextHandle , ManaSiphon);
	
	FGameplayModifierEvaluatedData EffData = FGameplayModifierEvaluatedData(UAuraAttributeSet::GetIncomingDamageAttribute() ,EGameplayModOp::Override , EffDamage);
	
	OutExecutionOutput.AddOutputModifier(EffData);
}
