// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AuraCharacterBase.h"
#include "EnemyInterface.h"
#include "Components/WidgetComponent.h"
#include "OverlapWidgetController.h"
#include "AuraEnemy.generated.h"


/**
 * 
 */
UCLASS()
class GAS_GAME_API AAuraEnemy : public AAuraCharacterBase , public IEnemyInterface
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay()override;

	UPROPERTY(EditAnywhere , BlueprintReadOnly)
	int32 Level = 1;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UWidgetComponent>HealthBar;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChanged OnMaxHealthChanged;
	
public:
	AAuraEnemy();

	virtual void  HeightLightActor()override ;

	virtual void  UnHeightLightActor()override;

	virtual void IniAbilityInfo() override;

	virtual int32 GetPlayerLevel()override;

private:
	void BindAttribute();
};
