// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AuraCharacterBase.h"
#include "Data/AbilitiyInfo.h"
#include "Interface/PlayerInterface.h"
#include "AuraCharacter.generated.h"

class UNiagaraComponent;
class UAudioComponent;
class UAuraAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class GAS_GAME_API AAuraCharacter : public AAuraCharacterBase,public IPlayerInterface
{
	GENERATED_BODY()
public:
	AAuraCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void PossessedBy(AController* NewController) override;

	virtual void OnRep_PlayerState()override;
	
	virtual void IniAbilityInfo() override;

	void GiveStartAbilities();

	virtual int32 GetPlayerLevel_Implementation();
	
	void SetLevel_Implementation(int InLevel);
	void SetExp_Implementation(float InExp);
	void AddExp_Implementation(float InExp);
	void AddLevel_Implementation(int InLevel);
	int32 GetExp_Implementation();
	int32 GetSpellPoints_Implementation();
	int32 GetTalentPoints_Implementation();
	void AddSpellPoints_Implementation(int32 InPoints);
	void AddTalentPoints_Implementation(int32 InPoints);

	UFUNCTION(Server ,Reliable)
	void Level_up();

	UFUNCTION(NetMulticast , Reliable)
	void PlayLevelEffect();

	void AddPointsAfterInitAttribute(UObject * Source);
protected:
	
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UGameplayAbility>> StartAbilitys;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UGameplayAbility>> BaseAbilitys;
	UPROPERTY(VisibleAnywhere,  BlueprintReadOnly)
	TObjectPtr<UNiagaraComponent>LevelUpNiagaraComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAudioComponent>LevelUpAudioComponent;
	
};  
