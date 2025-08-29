
#pragma once
#include "GameplayEffectTypes.h"
#include "GameplayTags.h"
#include "AuraGameplayEffectTypes.generated.h"

/**
 *   承载 着 一个技能 的 大部分参数
 */
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

	UPROPERTY()
	float DeathImpulseMagnitude = 0.f;

	UPROPERTY()
	FVector DeathImpulseDirection = FVector::Zero();

	UPROPERTY()
	float KnockBackMagnitude = 0.f;

	UPROPERTY()
	FVector KnockBackDirection = FVector::Zero();

	UPROPERTY()
	bool bShouldKnockBack = false;
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
	void SetDeathDirection(const FVector &InFVector);
	void SetKnockBackDirection(const FVector & InFVector);
	void SetLifeSiphon(const float & InLifeSiphon);
	void SetManaSiphon(const float & InManaSiphon);


	float GetLifeSiphon() const;
	float GetManaSiphon() const;
	float GetDebuffDuration()const;
	float GetDebuffFrequency()const;
	float GetDebuffDamage()const;
	bool GetIsDebuff()const;
	FVector GetDeathVector()const;
	FVector GetKnockBackDirection()const;
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

	UPROPERTY()
	FVector DeathImpulseDirection = FVector::Zero();

	UPROPERTY()
	FVector KnockBackDirection = FVector::Zero();

	UPROPERTY()
	float LifeSiphon = 0.f;

	UPROPERTY()
	float ManaSiphon = 0.f;
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
