// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "AuraPlayerState.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterStatChange , int32,ChangeValue);

class UAuraAbilitySystemComponent;
class UAuraAttributeSet;
class ULevelInfo;



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
	
	int32 GetPlayerLevel()const{ return Level; }
	int32 GetTalentPoints()const{return TalentPoints;}
	int32 GetSpellPoints()const{return SpellPoints;}
	int32 GetExp()const{return Experience;}
	virtual void  GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UFUNCTION(BlueprintCallable)
	float GetExpPercent(int32 NowExp);
	
	UFUNCTION(BlueprintCallable)
	void SetLevel(int InLevel);

	UFUNCTION(BlueprintCallable)
	void SetExp(int32 InExp);
	
	UFUNCTION(BlueprintCallable)
	void AddExp(int32 InExp);
	
	UFUNCTION(BlueprintCallable)
	void AddLevel(int InLevel);

	UFUNCTION()
	void AddSpellPoints(int32 InSpellPoints);

	UFUNCTION()
	void SetSpellPoints(int32 InSpellPoints);

	UFUNCTION()
	void AddTalentPoints(int32 InTalentPoints);

	UFUNCTION()
	void SetTalentPoints(int32 InTalentsPoints);
	
	void InitXpAndLevel()const;


	FOnCharacterStatChange OnExpChangePs;
	FOnCharacterStatChange OnLevelChangePs;
	FOnCharacterStatChange OnSpellPointsChangePs;
	FOnCharacterStatChange OnTalentPointsChnagePs;	
protected:

	UPROPERTY(VisibleAnywhere , BlueprintReadOnly)
	TObjectPtr<UAuraAbilitySystemComponent>AbilityComponent;

	UPROPERTY()
	TObjectPtr<UAuraAttributeSet>AttributeSet;

	UPROPERTY(VisibleDefaultsOnly ,BlueprintReadOnly , ReplicatedUsing = On_RepLevel , Category = "Attribute")
	int32 Level = 1;

	UPROPERTY(VisibleDefaultsOnly  ,BlueprintReadOnly , ReplicatedUsing = On_RepExp , Category = "Attribute")
	int32 Experience = 10;

	UPROPERTY(VisibleDefaultsOnly  ,BlueprintReadOnly , ReplicatedUsing = On_RepSpellPoints , Category = "Attribute")
	int32 SpellPoints = 0;

	UPROPERTY(VisibleDefaultsOnly  ,BlueprintReadOnly , ReplicatedUsing = On_RepTalentPoints , Category = "Attribute")
	int32 TalentPoints = 0;
	
	

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<ULevelInfo>LevelInfos;
	
	UFUNCTION()
	void Level_Up();
	UFUNCTION()
	void On_RepLevel()const;
	UFUNCTION()
	void On_RepExp()const;
	UFUNCTION()
	void On_RepSpellPoints()const;
	UFUNCTION()
	void On_RepTalentPoints()const;


};
