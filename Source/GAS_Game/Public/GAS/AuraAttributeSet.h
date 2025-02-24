// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectTypes.h"
#include "AuraAttributeSet.generated.h"





using TAttributeFunptr = FGameplayAttribute(*)();

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
	void ShowText(const FGameplayEffectModCallbackData& Data, AActor* SourceActor, AActor* TargetActor);
	void SendXp(AActor* SourceActor, AActor* TargetActor);


	TMap<FGameplayTag, TAttributeFunptr> TagsToAttributes;


	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_Strength, Category = "Attributes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Strength); 


	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_Vigor, Category = "Attributes")
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Vigor);


	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_Intelligence, Category = "Attributes")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Intelligence);


	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_Resilience, Category = "Attributes")
	FGameplayAttributeData Resilience;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resilience);

	UPROPERTY()
	FGameplayAttributeData IncomingDamage;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, IncomingDamage);

	UPROPERTY()
	FGameplayAttributeData IncomingExp;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, IncomingExp);
	
	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_BlockChance, Category = "Attributes")
	FGameplayAttributeData BlockChance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, BlockChance);


	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_Armor, Category = "Attributes")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Armor);



	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_ArmorPenetration, Category = "Attributes")
	FGameplayAttributeData ArmorPenetration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ArmorPenetration);



	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_CriticalHitChance, Category = "Attributes")
	FGameplayAttributeData CriticalHitChance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitChance);


	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_CriticalHitDamage, Category = "Attributes")
	FGameplayAttributeData CriticalHitDamage;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitDamage);

	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_CriticalHitResistance, Category = "Attributes")
	FGameplayAttributeData CriticalHitResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitResistance);

	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_HealthRegeneration, Category = "Attributes")
	FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, HealthRegeneration);

	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_ManaRegeneration, Category = "Attributes")
	FGameplayAttributeData ManaRegeneration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ManaRegeneration);



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

	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_FireResistance, Category = "Attributes")
	FGameplayAttributeData FireResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, FireResistance);

	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_ArcaneResistance, Category = "Attributes")
	FGameplayAttributeData ArcaneResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ArcaneResistance);

	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_PhysicsResistance, Category = "Attributes")
	FGameplayAttributeData PhysicsResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, PhysicsResistance);



	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_LightningResistance, Category = "Attributes")
	FGameplayAttributeData LightningResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, LightningResistance);



	
protected:


	
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData & OldHealth)const;

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana)const ;

	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana)const;




	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength)const;

	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& OldVigor)const;

	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence)const;

	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData& OldResilience)const;

	UFUNCTION()
	void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance)const;

	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldArmor)const;

	UFUNCTION()
	void OnRep_ArmorPenetration(const FGameplayAttributeData& OldMaxMana)const;

	UFUNCTION()
	void OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance)const;

	UFUNCTION()
	void OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance)const;

	UFUNCTION()
	void OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration)const;

	UFUNCTION()
	void OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration)const;

	
	UFUNCTION()
	void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage)const;

	UFUNCTION()
	void OnRep_FireResistance(const FGameplayAttributeData& OldFireResistance)const;

	UFUNCTION()
	void OnRep_LightningResistance(const FGameplayAttributeData& OldLightningResistance)const;

	UFUNCTION()
	void OnRep_ArcaneResistance(const FGameplayAttributeData& OldArcaneResistance)const;

	UFUNCTION()
	void OnRep_PhysicsResistance(const FGameplayAttributeData& OldPhysicsResistance)const;
};
