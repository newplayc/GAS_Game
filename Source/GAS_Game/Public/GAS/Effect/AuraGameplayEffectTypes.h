
#pragma once
#include "GameplayEffectTypes.h"
#include "GameplayTags.h"
#include "AuraGameplayEffectTypes.generated.h"
USTRUCT(BlueprintType)
struct FEffectParams
{
	GENERATED_BODY()

	
	UPROPERTY()
	FGameplayEffectSpecHandle EffectSpecHandle;
	
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent>SourceAbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent>TargetAbilitySystemComponent;
	
	UPROPERTY()
	float DebuffChance = 0.f;

	UPROPERTY()
	float DebuffDuration = 0.f;

	UPROPERTY()
	float DebuffFrequency = 0.f;

	UPROPERTY()
	float DebuffDamage = 0.f;

	UPROPERTY()
	float BaseDamage = 0.f;

	UPROPERTY()
	float AbilityLevel = 0.f;

	UPROPERTY()
	FGameplayTag DamageTypeTag = FGameplayTag();
	
};

USTRUCT(BlueprintType)
struct FAuraGameplayEffectContext : public FGameplayEffectContext
{

	GENERATED_BODY()
	
	void SetbBlock(  bool bBlock);
	void SetbCritical(bool bCritical);
	bool GetbCritical() const;
	bool GetbBlock() const;

	
	void SetDebuffDuration(float InDebuffDuration);
	void SetDebuffFrequency(float InDebuffFrequency);
	void SetDebuffDamage(float InDebuffDamage);
	void SetIsDebuff(bool InIsDebuff);
	void SetDamageTypeTag(TSharedPtr<FGameplayTag> DamageTag);
	
	
	float GetDebuffDuration()const;
	float GetDebuffFrequency()const;
	float GetDebuffDamage()const;
	bool GetIsDebuff()const;
	FGameplayTag GetDamageTypeTag()const;
	
	virtual UScriptStruct* GetScriptStruct() const override
	{
		return StaticStruct();
	}

	virtual FGameplayEffectContext* Duplicate() const override;

	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess) override;

protected:
	UPROPERTY(BlueprintReadOnly)
	bool bCriticalHit = false;

	UPROPERTY(BlueprintReadOnly)
	bool bBlockHit = false;

	UPROPERTY()
	float DebuffDuration = 0.f;

	UPROPERTY()
	float DebuffFrequency = 0.f;

	UPROPERTY()
	float DebuffDamage = 0.f;

	UPROPERTY()
	bool IsDebuff = false;
	
	TSharedPtr<FGameplayTag>DamageTypeTag;
	
};

template<>
struct TStructOpsTypeTraits<FAuraGameplayEffectContext>:TStructOpsTypeTraitsBase2<FAuraGameplayEffectContext>
{
	enum
	{
		WithNetSerializer = true,
		WithCopy =true
	};
};
