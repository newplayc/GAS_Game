// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

class UAuraAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class GAS_GAME_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()
public:
	AAuraCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;


	virtual void PossessedBy(AController* NewController) override;

	virtual void OnRep_PlayerState()override;

	void IniAbilityInfo();
};
