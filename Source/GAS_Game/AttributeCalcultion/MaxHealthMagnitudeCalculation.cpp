// Fill out your copyright notice in the Description page of Project Settings.


#include "MaxHealthMagnitudeCalculation.h"



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

	IICombatInterface* Interface = Cast<IICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = Interface->GetPlayerLevel();

	return 80.f + 2.5f * Vigor + 10.f * PlayerLevel;

}
