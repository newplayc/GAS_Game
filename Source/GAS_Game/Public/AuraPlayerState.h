// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "AuraPlayerState.generated.h"


class UAuraAbilitySystemComponent;
class UAuraAttributeSet;

/**
 * 
 */
UCLASS()
class GAS_GAME_API AAuraPlayerState : public APlayerState , public IAbilitySystemInterface
{
	GENERATED_BODY()
public:

	AAuraPlayerState();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual UAuraAttributeSet* GetAttributeSet() const { return AttributeSet; }
	
	int32 GetPlayerLevel(){ return Level; }

	virtual void  GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
protected:

	UPROPERTY(VisibleAnywhere , BlueprintReadOnly)
	TObjectPtr<UAuraAbilitySystemComponent>AbilityComponent;

	UPROPERTY()
	TObjectPtr<UAuraAttributeSet>AttributeSet;

	UPROPERTY(EditAnywhere ,  BlueprintReadOnly , ReplicatedUsing = On_RepLevel , Category = "Attribute")
	int32 Level = 1;

	UFUNCTION()
	void On_RepLevel();
	
};
