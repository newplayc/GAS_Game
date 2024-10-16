// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputDataConfig.h"
#include "AuraPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IEnemyInterface;
/**
* 
* 
* 
*/


UCLASS()
class GAS_GAME_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AAuraPlayerController();
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent()override;
	virtual void PlayerTick(float DeltaTime)override;


	UPROPERTY(BlueprintReadOnly)
	float show;
private:
	UPROPERTY(EditAnyWhere, Category = "Input")
	TObjectPtr<UInputMappingContext>AuraContext;

	UPROPERTY(EditAnywhere , Category = "input")
	TObjectPtr<UInputAction>MoveAction;

	void Move(const FInputActionValue& InputActionValue);
	
	void CheckUnderCursor();

	IEnemyInterface* HeightActor;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputDataConfig>InputAction;

	void PressFunction(FGameplayTag ActionTag);
	void ReleaseFunction(FGameplayTag ActionTag);
	void HeldFunction(FGameplayTag ActionTag);
};
