// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemInterface.h"
#include "Interface/ICombatInterface.h"
#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "Data/CharacterDataInfo.h"
#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"

class UAuraAbilitySystemComponent;
class UAuraAttributeSet;
class UAttributeSet;
class UDebuffNiagaraComponent;



UCLASS(abstract)
class GAS_GAME_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface, public IICombatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAuraCharacterBase();
	
	virtual void InitAttribute(UObject * Source);
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void IniAbilityInfo();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual UAuraAttributeSet* GetAttributeSet() const { return AttributeSet; }

	virtual UAnimMontage * GetAnimReactMontage_Implementation() override;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> ReactAnimMontage;

	UPROPERTY(EditAnywhere , BlueprintReadWrite, Category = "weapon")
	TObjectPtr<USkeletalMeshComponent>Weapon;

	UPROPERTY(VisibleAnywhere , BlueprintReadOnly)
	TObjectPtr<UAuraAbilitySystemComponent>AbilityComponent;

	UPROPERTY()
	TObjectPtr<UAuraAttributeSet>AttributeSet;

	UPROPERTY(VisibleAnywhere ,BlueprintReadOnly)
	TObjectPtr<UDebuffNiagaraComponent>FireDebuffNiagaraComponent;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TObjectPtr<UDebuffNiagaraComponent>StunDebuffNiagaraComponent;
	
	UPROPERTY(EditDefaultsOnly)
	ECharacterClass CharacterClass;

	
	
	UPROPERTY(EditAnywhere)
	FName WeaponSocketName;

	UPROPERTY(EditAnywhere)
	FName LeftHandSocketName;

	UPROPERTY(EditAnywhere)
	FName RightHandSocketName;

	UPROPERTY(EditAnywhere)
	FName RightTraildSocketName;

	UPROPERTY(EditAnywhere)
	FName LeftTrailSocketName;

	
	UPROPERTY(EditAnywhere , BlueprintReadOnly)
	TSubclassOf<UGameplayEffect>InitalPrimaryEffect;


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect>InitalSecondaryEffect;


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect>InitalVitalEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> WeaponDissolve;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UMaterialInstance>MeshDissolve;

	UPROPERTY(EditDefaultsOnly , BlueprintReadOnly)
	TArray<FTagMontage>AttackMontage;


	UPROPERTY(EditAnywhere , BlueprintReadOnly)
	TObjectPtr<UNiagaraSystem> BloodEffect;

	UPROPERTY(EditAnywhere , BlueprintReadOnly)
	TObjectPtr<USoundBase>DeathSound;
	
	UFUNCTION(BlueprintImplementableEvent , BlueprintCallable)
	void TimeLineSetWeaponMaterial();

	UFUNCTION(BlueprintImplementableEvent , BlueprintCallable)
	void TimeLineSetMeshMaterial();

	virtual void OnStunTagChanged(FGameplayTag StunTag, int32 count); 
	
	UPROPERTY(BlueprintReadWrite)
	int32 NumSummon = 0;
	
	bool IsDead = false;

	
	UPROPERTY(BlueprintReadOnly ,ReplicatedUsing= OnRep_Stun)
	bool IsStun = false;
	
	UFUNCTION()
	virtual void OnRep_Stun() const;

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	void HasDied_Implementation(const FVector & DeathVector);
	
	void AddKnockBack_Implementation(FVector& InVector) override;

	int32 GetSummonNum_Implementation();

	void ChangeSummonNum_Implementation(int32 Num);
	void DissolveMesh();

	UFUNCTION(NetMulticast, Reliable)
	virtual void NetDeath(const FVector& DeathVector);
	
	FVector GetWeaponSocketLocation_Implementation(FGameplayTag AttackTag);
	
	ECharacterClass GetCharacterClass_Implementation() ;

	bool IsDead_Implementation();

	TArray<FTagMontage> GetAttackMontage_Implementation();

	void SetDead_Implementation(bool bisDead);

	UNiagaraSystem * GetBloodEffect_Implementation();
	
};