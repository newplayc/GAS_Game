// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/DebuffNiagaraComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Tag/AuraGameplayTags.h"


UDebuffNiagaraComponent::UDebuffNiagaraComponent()
{
	bAutoActivate = false;
}


void UDebuffNiagaraComponent::BeginPlay()
{
	Super::BeginPlay();
	if(UAbilitySystemComponent * AbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwner()))
	{
		AbilitySystemComponent->RegisterGameplayTagEvent(FAuraGameplayTags::Get().Debuff_Burn).AddLambda([this](const FGameplayTag DebuffTag ,int32 Stack)
		{
			if(Stack > 0)
			{
				Activate();
			}
			else
			{
				Deactivate();
			}
		});
	}
	

}
