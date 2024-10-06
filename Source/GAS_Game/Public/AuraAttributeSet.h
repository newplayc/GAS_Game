// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilities/Public/GameplayEffectExtension.h"
#include "GameplayEffectTypes.h"
#include "AuraAttributeSet.generated.h"



USTRUCT(BlueprintType)
struct FEffectProperties
{

	GENERATED_BODY()

	FEffectProperties(){}

	UPROPERTY()
	UAbilitySystemComponent * SourceASC;

	UPROPERTY()
	AActor * SourceAvataActor;

	UPROPERTY()
	AController * SourceController;

	UPROPERTY()
	ACharacter * SourceCharacter;

	UPROPERTY()
	FGameplayEffectContextHandle EffectContextHandle;


	UPROPERTY()
	UAbilitySystemComponent* TargetASC;

	UPROPERTY()
	AActor* TargetAvataActor;

	UPROPERTY()
	AController* TargetController;

	UPROPERTY()
	ACharacter* TargetCharacter;

};


 #define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
/**
 * 
 */
UCLASS()
class GAS_GAME_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:


	UAuraAttributeSet();

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& EP) const;



	UPROPERTY(BlueprintReadWrite , ReplicatedUsing = OnRep_Health , Category = "Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health);



	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_MaxHealth, Category = "Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth);



	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_Mana, Category = "Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana);



	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_MaxMana, Category = "Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana);

	UPROPERTY()
	FEffectProperties EffectProperties;

	
protected:

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData & OldHealth)const;

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);

	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana);

	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana);


};
