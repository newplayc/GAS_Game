// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "NiagaraComponent.h"
#include "BuffHaloComponent.generated.h"

/**
 * 
 */
UCLASS()
class GAS_GAME_API UBuffHaloComponent : public UNiagaraComponent
{
	GENERATED_BODY()

	UBuffHaloComponent();

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag PassiveTag;

	UFUNCTION()
	void OnPassiveSpellChanged(const FGameplayTag &SpellTag , bool AOE);

	virtual  void BeginPlay() override;
	
};
