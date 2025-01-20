// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AuraCharacterBase.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Interface/EnemyInterface.h"
#include "Components/WidgetComponent.h"
#include "PlayerController/AuraAiController.h"
#include "WidgetController/OverlapWidgetController.h"
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

	bool bHitReacting = false;

	UPROPERTY(EditAnywhere)
	float LifeSpan = 5.0f;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UBehaviorTree>BehaviorTree;

	UPROPERTY()
	AAuraAiController* AIController;

	UPROPERTY()
	AActor * TargetEnemy = nullptr;
	
	void ReactTagChange(const FGameplayTag Tag , int32 count);
	
	void HasDied_Implementation();

	AActor* GetTargetActor_Implementation();

	void SetTargetActor_Implementation(AActor* TargetActor);

	
public:
	AAuraEnemy();

	virtual void  HeightLightActor()override ;

	virtual void  UnHeightLightActor()override;

	virtual void IniAbilityInfo() override;

	int32 GetPlayerLevel_Implementation();

	virtual void InitAttribute(UObject* Source) override;


	
private:
	void BindAttribute();

	virtual void PossessedBy(AController* NewController) override;
	const float EnemySpeed =450.f;

	
};
