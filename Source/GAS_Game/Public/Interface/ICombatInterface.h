// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovieSceneSection.h"
#include "NiagaraSystem.h"
#include "Data/CharacterDataInfo.h"
#include "UObject/Interface.h"
#include "ICombatInterface.generated.h"
UENUM(BlueprintType)
enum class EAttackType : uint8
{
	Remote,
	Melee
};


USTRUCT(BlueprintType , Blueprintable)
struct FTagMontage
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly , BlueprintReadOnly)
	 EAttackType  AttType;
		
	UPROPERTY(EditDefaultsOnly , BlueprintReadOnly)
	FGameplayTag MontageTag;

	UPROPERTY(EditDefaultsOnly , BlueprintReadOnly)
	FGameplayTag SocketTag;

	UPROPERTY(EditDefaultsOnly , BlueprintReadOnly)
	TObjectPtr<UAnimMontage>AttackMontage;

	UPROPERTY(EditDefaultsOnly ,BlueprintReadOnly)
	TObjectPtr<USoundBase>ImpactSound;

	bool operator==(const FTagMontage& it) const
	{
		return AttType ==  it.AttType &&
			MontageTag == it.MontageTag &&
			AttackMontage == it.AttackMontage &&
			ImpactSound == it.ImpactSound&&
			SocketTag == it.SocketTag;
	}
};



UINTERFACE(MinimalAPI , BlueprintType)
class UICombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAS_GAME_API IICombatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	int32 GetPlayerLevel();

	UFUNCTION(BlueprintCallable , BlueprintNativeEvent)
	FVector GetWeaponSocketLocation(FGameplayTag AttackTag);

	
	UFUNCTION(BlueprintCallable , BlueprintImplementableEvent)
	void WrapActorInterface(FVector Target);
	
	UFUNCTION(BlueprintNativeEvent , BlueprintCallable)
	UAnimMontage* GetAnimReactMontage();
	
	UFUNCTION(BlueprintNativeEvent , BlueprintCallable)
	 void  HasDied();

	UFUNCTION(BlueprintNativeEvent , BlueprintCallable)
	bool IsDead();
	
	UFUNCTION(BlueprintCallable , BlueprintNativeEvent)
	void SetDead(bool bisDead);

	UFUNCTION(BlueprintCallable , BlueprintNativeEvent)
	TArray<FTagMontage> GetAttackMontage();

	UFUNCTION(BlueprintCallable , BlueprintNativeEvent)
	UNiagaraSystem *  GetBloodEffect();
	
	virtual ECharacterClass GetCharacterClass()= 0;
	

	

};
