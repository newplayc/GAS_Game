// Fill out your copyright notice in the Description page of Project Settings.


#include "MaxHealthMagnitudeCalculation.h"
#include "GAS/AuraAttributeSet.h"
#include "Interface/ICombatInterface.h"

UMaxHealthMagnitudeCalculation::UMaxHealthMagnitudeCalculation()
{
	VigorDef.AttributeToCapture = UAuraAttributeSet::GetVigorAttribute();
	VigorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	VigorDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(VigorDef);
}

float UMaxHealthMagnitudeCalculation::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters AggregatorParameters;
	AggregatorParameters.SourceTags = SourceTags;
	AggregatorParameters.TargetTags = TargetTags;
	float Vigor = 0.f;
	GetCapturedAttributeMagnitude(VigorDef, Spec, AggregatorParameters,Vigor);
	Vigor = FMath::Max<float>(Vigor, 0.f);

	UObject* obj = Spec.GetContext().GetSourceObject();


	if(obj->Implements<UICombatInterface>())
	{
		const int PlayerLevel = IICombatInterface::Execute_GetPlayerLevel(obj);
		return 80.f + 2.5f * Vigor + 10.f * PlayerLevel;
	}
	return 0;
	

}
