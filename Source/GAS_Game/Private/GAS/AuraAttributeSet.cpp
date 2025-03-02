// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AuraAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AuraBlueprintFunctionLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Tag/AuraGameplayTags.h"
#include "PlayerController/AuraPlayerController.h"
#include "Interface/ICombatInterface.h"
#include "GameFramework/Character.h"
#include "GameplayEffectTypes.h"
#include "GameplayEffectExtension.h"
#include "GAS/Effect/AuraGameplayEffectTypes.h"
#include "Interface/PlayerInterface.h"
#include "GameplayEffect.h"
#include "GameplayEffectComponents/TargetTagsGameplayEffectComponent.h"


UAuraAttributeSet::UAuraAttributeSet()
{
	const FAuraGameplayTags & GameplayTags = FAuraGameplayTags::Get();
	
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Strength, GetStrengthAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Vigor, GetVigorAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Resilience, GetResilienceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Intelligence, GetIntelligenceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_Armor, GetArmorAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_ArmorPenetration, GetArmorPenetrationAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_BlockChance, GetBlockChanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_CriticalHitChance, GetCriticalHitChanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_CriticalHitDamage, GetCriticalHitDamageAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_CriticalHitResistance, GetCriticalHitResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_HealthRegeneration, GetHealthRegenerationAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_ManaRegeneration, GetManaRegenerationAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_MaxHealth, GetMaxHealthAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_MaxMana, GetMaxManaAttribute);

	TagsToAttributes.Add(GameplayTags.Attributes_Resistance_FireResistance, GetFireResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Resistance_ArcaneResistance, GetArcaneResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Resistance_LightningResistance, GetLightningResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Resistance_PhysicsResistance, GetPhysicsResistanceAttribute);
}




void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);



	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Vigor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Resilience, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, BlockChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ArmorPenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalHitChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalHitDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalHitResistance, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, HealthRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ManaRegeneration, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, FireResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, LightningResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ArcaneResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, PhysicsResistance, COND_None, REPNOTIFY_Always);


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
		
		if(EP.SourceASC->AbilityActorInfo.Get()->PlayerController.IsValid())
		EP.SourceController = EP.SourceASC->AbilityActorInfo.Get()->PlayerController.Get();
		
		if (EP.SourceController == nullptr && EP.SourceAvataActor !=nullptr)
		{
			
			APawn* P = Cast<APawn>(EP.SourceAvataActor);
			if (P)
			{
				EP.SourceController = P->GetController();
			}
		}
		if(EP.SourceController!=nullptr)
		{

			EP.SourceCharacter =  EP.SourceController->GetCharacter();
		}

		
	}


	 if(Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo.Get()->AvatarActor.IsValid())
	{
	 	
		 EP.TargetAvataActor = Data.Target.AbilityActorInfo.Get()->AvatarActor.Get();
	 	
		 if(Data.Target.AbilityActorInfo.Get()->PlayerController.IsValid())
		 EP.TargetController = Data.Target.AbilityActorInfo.Get()->PlayerController.Get();
	 	
	 	if(EP.TargetController == nullptr && EP.TargetAvataActor!=nullptr)
	 	{
	 		const APawn * p = Cast<APawn>(EP.TargetAvataActor);
	 		EP.TargetController = p->GetController();
	 	}
	 	
	 	EP.TargetASC = Data.Target.AbilityActorInfo.Get()->AbilitySystemComponent.Get();
	 	
	 	EP.TargetCharacter = EP.TargetController->GetCharacter();
	}
}



void UAuraAttributeSet::ShowText(const FGameplayEffectModCallbackData& Data, AActor* SourceActor, AActor* TargetActor) const
{
	if(SourceActor)
	{
		AAuraPlayerController * Pc = Cast<AAuraPlayerController>(Cast<ACharacter>(SourceActor)->GetController());
		if(Pc)
		{
			Pc->SetDamageText(GetIncomingDamage() ,Cast<ACharacter>(TargetActor) ,Data.EffectSpec.GetContext());
			return;
		}
		Pc = Cast<AAuraPlayerController>(Cast<ACharacter>(TargetActor)->GetController());
		if(Pc)
		{
			Pc->SetDamageText(GetIncomingDamage() ,Cast<ACharacter>(TargetActor) ,Data.EffectSpec.GetContext());
		}
			
	}

}

void UAuraAttributeSet::SendXp(AActor* SourceActor, AActor* TargetActor)
{
	float Exp = UAuraBlueprintFunctionLibrary::GetCharacterExpValue(TargetActor,IICombatInterface::Execute_GetCharacterClass(TargetActor) ,IICombatInterface::Execute_GetPlayerLevel(TargetActor));

	FGameplayTag ExpTag= FAuraGameplayTags::Get().Attributes_Meta_InComingExp;
	FGameplayEventData EventData;
	EventData.EventMagnitude = Exp;
	EventData.EventTag = ExpTag;
	
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(SourceActor , ExpTag ,EventData);
}

/*
 * 在Effect执行后执行的函数
 */
void UAuraAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	//FEffectProperties Properties;
	//SetEffectProperties(Data, Properties);

	AActor * SourceActor = Data.EffectSpec.GetContext().Get()->GetOriginalInstigatorAbilitySystemComponent()->GetAvatarActor();
	AActor * TargetActor = Data.Target.GetAvatarActor();
	if(TargetActor->Implements<UICombatInterface>())
	{
		if(IICombatInterface::Execute_IsDead(TargetActor))return;
	}
	
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
	}

		UAbilitySystemComponent * SourceAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(SourceActor);
		UAbilitySystemComponent * TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if(!SourceActor || !TargetActor)return;
		
	if(Data.EvaluatedData.Attribute==  GetIncomingDamageAttribute())
	{
		const float NewHealth = GetHealth() - GetIncomingDamage();
		SetHealth(FMath::Clamp(NewHealth, 0.f, GetMaxHealth()));
		ShowText(Data, SourceActor, TargetActor);
		
		const bool IsDied = NewHealth <=0;
		/* 没死 */ 
		if(!IsDied)
		{
			FGameplayTagContainer TempTags = FGameplayTagContainer();
			TempTags.AddTag(FAuraGameplayTags::Get().Effects_React);
			Data.Target.TryActivateAbilitiesByTag(TempTags);
		}
		else
		{
			if( TargetActor->Implements<UICombatInterface>())
			{
				
				IICombatInterface::Execute_SetDead(TargetActor , true);
				IICombatInterface::Execute_HasDied(TargetActor);
				
				SendXp(SourceActor, TargetActor);
			}
		}
	}
	
	if(Data.EvaluatedData.Attribute == GetIncomingExpAttribute())
	{
		if(SourceActor->Implements<UPlayerInterface>())
		{
			IPlayerInterface::Execute_AddExp(SourceActor , GetIncomingExp());
		}
	}

	bool IsDebuff = UAuraBlueprintFunctionLibrary::GetIsDebuffFromContext(Data.EffectSpec.GetContext());
	if(IsDebuff)
	{
		
		FGameplayEffectContextHandle EffectContextHandle = SourceAbilitySystemComponent->MakeEffectContext();
		EffectContextHandle.AddSourceObject(SourceActor);
		
		float DebuffDuration = UAuraBlueprintFunctionLibrary::GetDebuffDuration(Data.EffectSpec.GetContext());
		float DebuffFrequency = UAuraBlueprintFunctionLibrary::GetDebuffFrequency(Data.EffectSpec.GetContext());
		float DebuffDamage = UAuraBlueprintFunctionLibrary::GetDebuffDamage(Data.EffectSpec.GetContext());
		FGameplayTag DamageTypeTag = UAuraBlueprintFunctionLibrary::GetDamageTypeTag(Data.EffectSpec.GetContext());

		FString DebuffName = FString::Printf(TEXT("DynamicDebuff_%s"), *DamageTypeTag.ToString());
		UGameplayEffect * DebuffEffect = NewObject<UGameplayEffect>(GetTransientPackage(),*DebuffName);
		DebuffEffect->DurationPolicy = EGameplayEffectDurationType::HasDuration;
		DebuffEffect->Period = DebuffFrequency;
		DebuffEffect->DurationMagnitude = FScalableFloat(DebuffDuration);


		
		// 
		FGameplayTag DebuffTag = FAuraGameplayTags::Get().DamageTypeToDebuff[DamageTypeTag];
		UTargetTagsGameplayEffectComponent & TargetEffectComponent =  DebuffEffect->FindOrAddComponent<UTargetTagsGameplayEffectComponent>();
		FInheritedTagContainer TagContainer;
		TagContainer.AddTag(DebuffTag);
		TargetEffectComponent.SetAndApplyTargetTagChanges(TagContainer);
		

		
		DebuffEffect->StackingType = EGameplayEffectStackingType::AggregateBySource;
		DebuffEffect->StackLimitCount = 1;


		
		FGameplayModifierInfo ModifierInfo;
		ModifierInfo.Attribute = GetIncomingDamageAttribute();
		ModifierInfo.ModifierOp = EGameplayModOp::Override;
		ModifierInfo.ModifierMagnitude = FScalableFloat(DebuffDamage);
		DebuffEffect->Modifiers.Add(ModifierInfo);

		
		if(FGameplayEffectSpec * MutableSpec = new FGameplayEffectSpec(DebuffEffect , EffectContextHandle , Data.EffectSpec.GetLevel()))
		{
			FAuraGameplayEffectContext* AuraContext = static_cast<FAuraGameplayEffectContext*>(MutableSpec->GetContext().Get());
			TSharedPtr<FGameplayTag> DebuffDamageType = MakeShareable(new FGameplayTag(DebuffTag));
			AuraContext->SetDamageTypeTag(DebuffDamageType);	
			TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*MutableSpec);
		}

		
	}
}




void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Health, OldHealth);
}

void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxHealth, OldMaxHealth);
}

void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana)const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Mana, OldMana);
}

void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana)const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxMana, OldMaxMana);
}


void UAuraAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Strength, OldStrength);
}


void UAuraAttributeSet::OnRep_Vigor(const FGameplayAttributeData& OldVigor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Vigor, OldVigor);
}


void UAuraAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Intelligence, OldIntelligence);
}

void UAuraAttributeSet::OnRep_Resilience(const FGameplayAttributeData& OldResilience) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Resilience, OldResilience);
}


void UAuraAttributeSet::OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, BlockChance, OldBlockChance);
}

void UAuraAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Armor, OldArmor);
}


void UAuraAttributeSet::OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ArmorPenetration, OldArmorPenetration);
}


void UAuraAttributeSet::OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitChance, OldCriticalHitChance);
}


void UAuraAttributeSet::OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitResistance, OldCriticalHitResistance);
}


void UAuraAttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, HealthRegeneration, OldHealthRegeneration);
}


void UAuraAttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ManaRegeneration, OldManaRegeneration);
}

void UAuraAttributeSet::OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitDamage, OldCriticalHitDamage);
}

void UAuraAttributeSet::OnRep_FireResistance(const FGameplayAttributeData& OldFireResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitDamage, OldFireResistance);
}

void UAuraAttributeSet::OnRep_LightningResistance(const FGameplayAttributeData& OldLightningResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitDamage, OldLightningResistance);
}

void UAuraAttributeSet::OnRep_ArcaneResistance(const FGameplayAttributeData& OldArcaneResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitDamage, OldArcaneResistance);
}

void UAuraAttributeSet::OnRep_PhysicsResistance(const FGameplayAttributeData& OldPhysicsResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitDamage, OldPhysicsResistance);
}
