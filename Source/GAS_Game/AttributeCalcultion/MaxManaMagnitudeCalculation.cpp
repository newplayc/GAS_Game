// Fill out your copyright notice in the Description page of Project Settings.



#include "MaxManaMagnitudeCalculation.h"
#include "GAS/AuraAttributeSet.h"
#include "Interface/ICombatInterface.h"

UMaxManaMagnitudeCalculation::UMaxManaMagnitudeCalculation()
{
	IntelligenceDef.AttributeToCapture = UAuraAttributeSet::GetIntelligenceAttribute();
	IntelligenceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	IntelligenceDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(IntelligenceDef);
}

float UMaxManaMagnitudeCalculation::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters AggregatorParameters;
	AggregatorParameters.SourceTags = SourceTags;
	AggregatorParameters.TargetTags = TargetTags;

	float Intelligence = 0.f;
	GetCapturedAttributeMagnitude(IntelligenceDef, Spec, AggregatorParameters, Intelligence);
	Intelligence = FMath::Max<float>(Intelligence, 0.f);

	IICombatInterface* Interface = Cast<IICombatInterface>(Spec.GetContext().GetSourceObject());
	int PlayerLevel = Interface->GetPlayerLevel();
	return  80.f + 2.5f * Intelligence + 10.f * PlayerLevel;
}
