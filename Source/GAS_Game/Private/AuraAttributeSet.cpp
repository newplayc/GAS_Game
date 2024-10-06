// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraAttributeSet.h"
#include "Net/UnrealNetwork.h"


UAuraAttributeSet::UAuraAttributeSet()
{
	InitHealth(50.f);
	InitMaxHealth(100.f);
	InitMana(50.f);
	InitMaxMana(100.f);
}




void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}

void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}
}

void UAuraAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& EP) const
{
	EP.EffectContextHandle = Data.EffectSpec.GetContext();

	EP.SourceASC = EP.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if (EP.SourceASC &&EP.SourceASC->AbilityActorInfo.IsValid()&& EP.SourceASC->AbilityActorInfo.Get()->AvatarActor.IsValid())
	{
		EP.SourceAvataActor = EP.SourceASC->AbilityActorInfo.Get()->AvatarActor.Get();
		EP.SourceController = EP.SourceASC->AbilityActorInfo.Get()->PlayerController.Get();
		if (EP.SourceController)
			EP.SourceCharacter = Cast<ACharacter>(EP.SourceController->GetCharacter());
		else if (EP.SourceController == nullptr && EP.SourceAvataActor != nullptr)
		{
			APawn* P = Cast<APawn>(EP.SourceAvataActor);
			if (P)
			{
				EP.SourceController = P->GetController();

			}
		}

		if (EP.SourceController)
		{
			EP.SourceCharacter = EP.SourceController->GetCharacter();
		}
	}


	 if(Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo.Get()->AvatarActor.IsValid())
	{
		 EP.TargetAvataActor = Data.Target.AbilityActorInfo.Get()->AvatarActor.Get();
		 EP.TargetController = Data.Target.AbilityActorInfo.Get()->PlayerController.Get();
		 EP.TargetASC = Data.Target.AbilityActorInfo.Get()->AbilitySystemComponent.Get();
		 EP.TargetCharacter = Cast<ACharacter>(EP.TargetAvataActor);

	}

}



void UAuraAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{

	Super::PostGameplayEffectExecute(Data);
	FEffectProperties Properties;


}

void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Health, OldHealth);
}

void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxHealth, OldMaxHealth);
}

void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Mana, OldMana);
}

void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxMana, OldMaxMana);
}
