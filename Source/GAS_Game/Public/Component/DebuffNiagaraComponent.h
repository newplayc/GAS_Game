// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraComponent.h"
#include "DebuffNiagaraComponent.generated.h"

/**
 * 
 */
UCLASS()
class GAS_GAME_API UDebuffNiagaraComponent : public UNiagaraComponent
{
	GENERATED_BODY()

	UDebuffNiagaraComponent();

	virtual void BeginPlay() override;
};
