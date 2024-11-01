// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemInterface.h"
#include "ICombatInterface.h"
#include "CoreMinimal.h"
#include "CharacterDataInfo.h"
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

	virtual UAnimMontage * GetAnimReactMontage_Implementation() override;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> ReactAnimMontage;

	UPROPERTY(EditAnywhere , BlueprintReadWrite, Category = "weapon")
	TObjectPtr<USkeletalMeshComponent>Weapon;

	UPROPERTY(VisibleAnywhere , BlueprintReadOnly)
	TObjectPtr<UAuraAbilitySystemComponent>AbilityComponent;

	UPROPERTY()
	TObjectPtr<UAuraAttributeSet>AttributeSet;

	UPROPERTY(EditDefaultsOnly)
	ECharacterClass CharacterClass;

	
	
	UPROPERTY(EditAnywhere)
	FName WeaponSocketName;

		
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
	
	UFUNCTION(BlueprintImplementableEvent , BlueprintCallable)
	void TimeLineSetWeaponMaterial();

	UFUNCTION(BlueprintImplementableEvent , BlueprintCallable)
	void TimeLineSetMeshMaterial();
	
	
	virtual void Died() override;
	
	void DissolveMesh();

	UFUNCTION(NetMulticast, Reliable)
	virtual void NetDeath();
	
	virtual void InitAttribute(UObject * Source); 

	virtual FVector GetWeaponSocketLocation() override;
	

	
};
