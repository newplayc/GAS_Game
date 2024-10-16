// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemInterface.h"
#include "ICombatInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"

class UAuraAbilitySystemComponent;
class UAuraAttributeSet;
class UAttributeSet;

UCLASS(abstract)
class GAS_GAME_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface, public IICombatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAuraCharacterBase();

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void IniAbilityInfo();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual UAuraAttributeSet* GetAttributeSet() const { return AttributeSet; }



	UPROPERTY(EditAnywhere , BlueprintReadWrite, Category = "weapon")
	TObjectPtr<USkeletalMeshComponent>Weapon;

	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent>AbilityComponent;

	UPROPERTY()
	TObjectPtr<UAuraAttributeSet>AttributeSet;


};
