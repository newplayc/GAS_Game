
#include "GAS/Effect/AuraGameplayEffectTypes.h"


void FAuraGameplayEffectContext::SetbBlock(bool bBlock)
{this->bBlockHit = bBlock;}

void FAuraGameplayEffectContext::SetbCritical(bool bCritical)
{this->bCriticalHit = bCritical;}

void FAuraGameplayEffectContext::SetDebuffDuration(float InDebuffDuration)
{
	DebuffDuration = InDebuffDuration;
}

void FAuraGameplayEffectContext::SetDebuffFrequency(float InDebuffFrequency)
{
	DebuffFrequency = InDebuffFrequency;
}

void FAuraGameplayEffectContext::SetDebuffDamage(float InDebuffDamage)
{
	DebuffDamage =  InDebuffDamage;
}

void FAuraGameplayEffectContext::SetIsDebuff(bool InIsDebuff)
{
	IsDebuff = InIsDebuff;
}

void FAuraGameplayEffectContext::SetDamageTypeTag(TSharedPtr<FGameplayTag>DamageTag)
{
	DamageTypeTag = DamageTag;
}

void FAuraGameplayEffectContext::SetDeathDirection(const FVector &InFVector)
{
	DeathImpulseDirection =  InFVector;
}

void FAuraGameplayEffectContext::SetKnockBackDirection(const FVector &InFVector)
{
	KnockBackDirection =  InFVector;
}

void FAuraGameplayEffectContext::SetLifeSiphon(const float& InLifeSiphon)
{
	LifeSiphon = InLifeSiphon;
}

void FAuraGameplayEffectContext::SetManaSiphon(const float& InManaSiphon)
{
	ManaSiphon = InManaSiphon;
}

float FAuraGameplayEffectContext::GetLifeSiphon() const
{
	return LifeSiphon;
}

float FAuraGameplayEffectContext::GetManaSiphon() const
{
	return ManaSiphon;
}

float FAuraGameplayEffectContext::GetDebuffDuration()const
{
	return DebuffDuration;
}

float FAuraGameplayEffectContext::GetDebuffFrequency()const
{
	return DebuffFrequency;
}

float FAuraGameplayEffectContext::GetDebuffDamage()const
{
	return DebuffDamage;
}

bool FAuraGameplayEffectContext::GetIsDebuff()const
{
	return IsDebuff;
}

FVector FAuraGameplayEffectContext::GetDeathVector()const
{
	return DeathImpulseDirection;
}

FVector FAuraGameplayEffectContext::GetKnockBackDirection() const
{
	return KnockBackDirection;
}

FGameplayTag FAuraGameplayEffectContext::GetDamageTypeTag() const
{
	return *DamageTypeTag.Get();
}

bool FAuraGameplayEffectContext::GetbCritical() const
{return this->bCriticalHit;}

bool FAuraGameplayEffectContext::GetbBlock() const
{return this->bBlockHit;}

FGameplayEffectContext* FAuraGameplayEffectContext::Duplicate() const
{
	FAuraGameplayEffectContext* NewContext = new FAuraGameplayEffectContext();
	*NewContext = *this;
	if (GetHitResult())
	{
		// Does a deep copy of the hit result
		NewContext->AddHitResult(*GetHitResult(), true);
	}
	return NewContext;
}

bool FAuraGameplayEffectContext::NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess)
{
	uint32 RepBits = 0;
	if (Ar.IsSaving())
	{
		if (bReplicateInstigator && Instigator.IsValid())
		{
			RepBits |= 1 << 0;
		}
		if (bReplicateEffectCauser && EffectCauser.IsValid() )
		{
			RepBits |= 1 << 1;
		}
		if (AbilityCDO.IsValid())
		{
			RepBits |= 1 << 2;
		}
		if (bReplicateSourceObject && SourceObject.IsValid())
		{
			RepBits |= 1 << 3;
		}
		if (Actors.Num() > 0)
		{
			RepBits |= 1 << 4;
		}
		if (HitResult.IsValid())
		{
			RepBits |= 1 << 5;
		}
		if (bHasWorldOrigin)
		{
			RepBits |= 1 << 6;
		}
		if(bCriticalHit)
		{
			RepBits |= 1 << 7;
		}
		if(bBlockHit)
		{
			RepBits |= 1 << 8;
		}
		if(DebuffDamage > 0.f)
		{
			RepBits |= 1<<9;
		}
		if(DebuffDuration > 0.f)
		{
			RepBits |= 1<<10;
		}
		if(DebuffFrequency >0.f)
		{
			RepBits |= 1 << 11;
		}
		if(true)
		{
			RepBits |= 1<<12;
		}
		if(DamageTypeTag.IsValid())
		{
			RepBits |= 1<<13;
		}
		if(!DeathImpulseDirection.IsZero())
		{
			RepBits |= 1<<14;
		}
		if(!KnockBackDirection.IsZero())
		{
			RepBits |= 1<<15;
		}
		if(LifeSiphon > 0)
		{
			RepBits |= 1<<16;
		}
		if(ManaSiphon > 0)
		{
			RepBits |= 1<<17;
		}
	}
	

	Ar.SerializeBits(&RepBits, 18);

	if (RepBits & (1 << 0))
	{
		Ar << Instigator;
	}
	if (RepBits & (1 << 1))
	{
		Ar << EffectCauser;
	}
	if (RepBits & (1 << 2))
	{
		Ar << AbilityCDO;
	}
	if (RepBits & (1 << 3))
	{
		Ar << SourceObject;
	}
	if (RepBits & (1 << 4))
	{
		SafeNetSerializeTArray_Default<31>(Ar, Actors);
	}
	if (RepBits & (1 << 5))
	{
		if (Ar.IsLoading())
		{
			if (!HitResult.IsValid())
			{
				HitResult = TSharedPtr<FHitResult>(new FHitResult());
			}
		}
		HitResult->NetSerialize(Ar, Map, bOutSuccess);
	}
	if (RepBits & (1 << 6))
	{
		Ar << WorldOrigin;
		bHasWorldOrigin = true;
	}
	else
	{
		bHasWorldOrigin = false;
	}
	if(RepBits & (1 << 7))
	{
		Ar<<bCriticalHit;
	}
	if(RepBits & (1 << 8))
	{
		Ar<<bBlockHit;
	}

	if(RepBits & (1<<12))
	{
		Ar << IsDebuff;
		if(RepBits & (1<<9))
		{
			Ar << DebuffDamage;
		}
		if(RepBits & (1<<10))
		{
			Ar << DebuffDuration;
		}

		if(RepBits & (1<<11))
		{
			Ar << DebuffFrequency;
		}
	}
	if (RepBits & (1 << 13))
	{
		if (Ar.IsLoading())
		{
			if (!DamageTypeTag.IsValid())
			{
				DamageTypeTag = MakeShared<FGameplayTag>();
			}
		}
		DamageTypeTag->NetSerialize(Ar, Map, bOutSuccess);
	}
	if(RepBits & (1<<14))
	{
		DeathImpulseDirection.NetSerialize(Ar,Map,bOutSuccess);
	}
	if(RepBits &(1<<15))
	{
		KnockBackDirection.NetSerialize(Ar,Map,bOutSuccess);
	}

	
	if(RepBits &(1<<16))
	{
		Ar<<LifeSiphon;
	}
	if(RepBits & (1<<17))
	{
		Ar<<ManaSiphon;
	}
	
	if (Ar.IsLoading())
	{
		AddInstigator(Instigator.Get(), EffectCauser.Get()); // Just to initialize InstigatorAbilitySystemComponent
	}	
	
	bOutSuccess = true;
	return true;
}

