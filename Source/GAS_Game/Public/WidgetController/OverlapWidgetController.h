
#pragma once

#include "CoreMinimal.h"
#include "AuraUserWidgetController.h"
#include "Data/AbilitiyInfo.h"
#include "Widget/AuraUserWidget.h"
#include "OverlapWidgetController.generated.h"


USTRUCT(BlueprintType)
struct FUIWidgetRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
	FGameplayTag MessageTag = FGameplayTag();

	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
	FText Message = FText();

	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
	TSubclassOf<UAuraUserWidget>MessageWidget;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
	UTexture2D* Image;
	
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChanged, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMessageWidgetRowDelegate, FUIWidgetRow , WidgetRow);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbilityAddDelegate , FAbilityInfo, AddInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStateChanged, int32 , ChnageValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnShowSpellDescription , FString, NowLevelDesription , FString, NextLevelDesription/**Now兼职 激活能力条件  */); 


UCLASS(BlueprintType , Blueprintable)
class GAS_GAME_API UOverlapWidgetController : public UAuraUserWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitailvalues()override;

	virtual void BindCallbacksToDependences() override;

	UPROPERTY(BlueprintAssignable , Category = "DelegateAttribute")
	FOnAttributeChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "DelegateAttribute")
	FOnAttributeChanged OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "DelegateAttribute")
	FOnAttributeChanged OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "DelegateAttribute")
	FOnAttributeChanged OnMaxManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "DelegateWidgetMessage")
	FOnMessageWidgetRowDelegate FWidgetDelegate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UDataTable> EffectMessageDataTable;

	UPROPERTY(EditAnywhere , BlueprintReadOnly)
	TObjectPtr<UAbilitiyInfo> AbilityInfos;

	UPROPERTY(BlueprintAssignable)
	FOnAbilityAddDelegate AbilitiyInfoDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnStateChanged ExpChanged;

	UPROPERTY(BlueprintAssignable)
	FOnStateChanged LevelChanged;

	UPROPERTY(BlueprintAssignable)
	FOnShowSpellDescription ShowSpellDescriptionDelegate;
	
	UFUNCTION()
	void OnPsExpBroadCast( int32 Exp);
		
	UFUNCTION()
	void OnPsLevelBroadCast( int32 Level);

	void OnAbilityBroadCast();

	
	UFUNCTION(BlueprintCallable)
	void DeleteAbilityBlueprintCall(const FGameplayTag& AbilityInput,const FGameplayTag& AbilityType);

	UFUNCTION(BlueprintCallable)
	void LevelChangeSpell(float Level , FGameplayTag AbilityTag);
	
	UFUNCTION(BlueprintCallable)
	void AddAbility(const FGameplayTag & SpellTag , const FGameplayTag & InputTag);
	
	void ChangeAbility(const FGameplayTag& AbilityTag) ;

	void DeleteInput(const FGameplayTag& InputTag) ;

}; 

