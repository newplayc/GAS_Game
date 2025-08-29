// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Data/InputDataConfig.h"
#include "WidgetComponent/DamageTextWidgetCom.h"
#include "GameplayEffectTypes.h"
#include "NiagaraSystem.h"
#include "OtherActor/AuraDecalActor.h"
#include "AuraPlayerController.generated.h"

class UAuraAbilitySystemComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IEnemyInterface;
class USplineComponent;

/**
* 
*/
UCLASS()
class GAS_GAME_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	
	
	UFUNCTION(Client , Reliable)
	void SetDamageText(float Damage, ACharacter * ECharacter ,const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(Client , Reliable)
	void SetLifeSiphonText(ACharacter * ECharacter , const FGameplayEffectContextHandle & EffectContextHandle);

	UFUNCTION(Client , Reliable)
	void SetManaSiphonText(ACharacter * ECharacter , const FGameplayEffectContextHandle & EffectContextHandle);

	UFUNCTION()
	void ShowDecal(UMaterialInterface * DecalMaterial);
	
	UFUNCTION()
	void HidenDecal();
	
protected:
	AAuraPlayerController();
	virtual void BeginPlay() override;
	virtual void SetupInputComponent()override;
	virtual void PlayerTick(float DeltaTime)override;
	

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UDamageTextWidgetCom>DamageTextWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AAuraDecalActor>DecalActorClass;

	UPROPERTY()
	TObjectPtr<AAuraDecalActor>DecalActorInstance;
	
private:
	UPROPERTY(EditAnyWhere, Category = "Input")
	TObjectPtr<UInputMappingContext>AuraContext;
	
	UPROPERTY(EditAnywhere , Category = "input")
	// ReSharper disable once UnrealHeaderToolError
	TObjectPtr<UInputAction>MoveAction;
	
	UPROPERTY(EditAnywhere, Category = "input")
	TObjectPtr<UInputAction>ShiftAction;

	UPROPERTY(EditDefaultsOnly ,Category="Icon")
	TObjectPtr<UNiagaraSystem>ClickIcon;
	
	void Move(const FInputActionValue& InputActionValue);

	void ShiftStart();

	void ShiftEnd();

	bool bShift = false;
	
	void CheckUnderCursor();
	FHitResult HitResult;
	
	IEnemyInterface* HeightActor;

	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputDataConfig>InputAction;
	
	void PressFunction(FGameplayTag ActionTag);
	
	void ReleaseFunction(FGameplayTag ActionTag);
	
	void HeldFunction(FGameplayTag ActionTag);
	
	UAuraAbilitySystemComponent*  GetGAS();
	
	UPROPERTY()
	UAuraAbilitySystemComponent * AbilitySystemCom;

	FVector CachedDestination = FVector::ZeroVector;

	float FollowTime = 0.f;

	float ShortPressThreshold = 0.5f;

	bool bAutoRunning = false;

	bool bTargeting = false;
	
	UPROPERTY(EditAnywhere)
	float AutoRunAcceptanceRadious = 50.f;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent>Spline; 

	// 点击 地面 之后自动走向目标 ，
	void AutoRun();
	
	void UpdateDecal();
};
