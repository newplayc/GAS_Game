// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "AuraUserWidgetController.generated.h"


class UAbilitySystemComponent;
class UAttributeSet;

USTRUCT(BlueprintType)
struct FWidgetContollerParams
{
	GENERATED_BODY()
	FWidgetContollerParams() {}

	FWidgetContollerParams(APlayerState* PS, APlayerController* PC, UAbilitySystemComponent* ASC, UAttributeSet* AS)
		: PlayerState(PS), PlayerController(PC), AbilitySystemComponent(ASC), AttributeSet(AS) {}


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerState>PlayerState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerController>PlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent>AbilitySystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAttributeSet>AttributeSet;
};
/**
 * 
 */
UCLASS()
class GAS_GAME_API UAuraUserWidgetController : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetParamas(const FWidgetContollerParams& WCParams);

	virtual void BroadcastInitailvalues();

	virtual void BindCallbacksToDependences();
protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<APlayerState>PlayerState;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<APlayerController>PlayerController;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UAbilitySystemComponent>AbilityComponent;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UAttributeSet>AttributeSet;
};
