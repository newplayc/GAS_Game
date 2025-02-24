// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Abilities/GameplayAbility.h"
#include "Engine/DataAsset.h"
#include "Tag/AuraGameplayTags.h"
#include "AbilitiyInfo.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FAbilityInfo
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite)
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly , BlueprintReadOnly)
	FGameplayTag AbilityTag;
	
	UPROPERTY(EditDefaultsOnly , BlueprintReadOnly)
	FGameplayTag CoolDownTag;
	
	UPROPERTY(EditDefaultsOnly , BlueprintReadOnly)
	TObjectPtr<UTexture>SpellIcon;

	UPROPERTY(BlueprintReadWrite ,meta=(MakeStructureDefaultValue = true) ,EditDefaultsOnly)
	FGameplayTag StateTag = FAuraGameplayTags::Get().Ability_State_Locked;

	UPROPERTY(EditDefaultsOnly , BlueprintReadOnly)
	TObjectPtr<UMaterialInstance>BackGround;

	UPROPERTY(EditDefaultsOnly , BlueprintReadOnly)
	int32 OpenLevel;

	UPROPERTY(EditDefaultsOnly , BlueprintReadOnly)
	TSubclassOf<UGameplayAbility>AbilityClass;
};


UCLASS(BlueprintType)
class GAS_GAME_API UAbilitiyInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly)
	TArray<FAbilityInfo>AbilityInfos;

	UFUNCTION(BlueprintCallable)
	FAbilityInfo FIndAbilityInfoWithTag(const FGameplayTag& AbilityTag)const;
	UFUNCTION(BlueprintCallable)
	FAbilityInfo SetAbilityStateTagWithAbilityTag(const FGameplayTag & AbilityTag , const FGameplayTag& StateTag);
	UFUNCTION(BlueprintCallable)
	FAbilityInfo SetAbilityInputTagWithAbilityTag(const FGameplayTag & AbilityTag , const FGameplayTag& InputTag);

};
