// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AuraCharacterBase.h"
#include "Component/BuffHaloComponent.h"
#include "Data/AbilitiyInfo.h"
#include "Interface/PlayerInterface.h"
#include "AuraCharacter.generated.h"

class UNiagaraComponent;
class UAudioComponent;
class UAuraAbilitySystemComponent;
/**
 * 
 */

DECLARE_MULTICAST_DELEGATE(FOnAbilitySystemComponent);


UCLASS()
class GAS_GAME_API AAuraCharacter : public AAuraCharacterBase,public IPlayerInterface
{
	GENERATED_BODY()
public:
	AAuraCharacter();

	// 当 GAS 有效时 Broadcast
	FOnAbilitySystemComponent OnAbilitySystemComponent;
	// 获取GAS
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	// 被麻痹的回调 添加 能力阻挡标签
	virtual void OnStunTagChanged(const FGameplayTag StunTag, int32 count) override;
	// 发生在服务器   调用了一系列初始化 
	virtual void PossessedBy(AController* NewController) override;
	// 发生在客户端
	virtual void OnRep_PlayerState()override;
	// 初始化一系列属性可 (看定义详细)
	virtual void IniAbilityInfo() override;
	// 初始化人物
	void InitAuraFromSlot();
	// 添加默认技能
	void GiveStartAbilities();

	virtual int32 GetPlayerLevel_Implementation();

	
	void SetLevel_Implementation(int32 InLevel);
	void SetExp_Implementation(float InExp);
	void AddExp_Implementation(float InExp);
	void AddLevel_Implementation(int32 InLevel);
	void SetSpellPoints_Implementation(int32 InPoints);
	void SetTalentPoints_Implementation(int32 InPoints);
	int32 GetExp_Implementation();
	int32 GetSpellPoints_Implementation();
	int32 GetTalentPoints_Implementation();
	void AddSpellPoints_Implementation(int32 InPoints);
	void AddTalentPoints_Implementation(int32 InPoints);
	USkeletalMeshComponent * GetWeaponMesh_Implementation() override;
	
	void SavePlayState_Implementation(const FName & PlayerStartTag) override;
	void ShowMagicCircle_Implementation(UMaterialInterface* MaterialInterface) override;
	void HidenMagicCircle_Implementation() override;

	
	UFUNCTION(Server ,Reliable)
	void Level_up();

	UFUNCTION(NetMulticast , Reliable)
	void PlayLevelEffect();
	
	virtual void OnRep_Stun() const override;
	
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
	
	UPROPERTY(VisibleAnywhere,  BlueprintReadOnly)
	TObjectPtr<UBuffHaloComponent>CriticalComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UBuffHaloComponent>HealthComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UBuffHaloComponent>ManaComponent;


	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect>InitPrimaryAttributeFromSlot;
};  
