
#pragma once
#include "GameplayEffectTypes.h"
#include "AuraGameplayEffectTypes.generated.h"


USTRUCT(BlueprintType)
struct FAuraGameplayEffectContext : public FGameplayEffectContext
{

	GENERATED_BODY()
	
	void SetbBlock(  bool bBlock);
	void SetbCritical(bool bCritical);

	bool GetbCritical() const;
	bool GetbBlock() const;

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
