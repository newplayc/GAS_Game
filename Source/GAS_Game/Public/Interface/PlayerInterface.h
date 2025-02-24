// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPlayerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAS_GAME_API IPlayerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent)
	void SetLevel(int InLevel);

	UFUNCTION(BlueprintNativeEvent)
	void SetExp(float InExp);
	
	UFUNCTION(BlueprintNativeEvent)
	void AddExp(float InExp);
	
	UFUNCTION(BlueprintNativeEvent)
	void AddLevel(int InLevel);

	UFUNCTION(BlueprintNativeEvent)
	int32 GetExp();

	
	UFUNCTION(BlueprintNativeEvent)
	int32 GetTalentPoints();

	UFUNCTION(BlueprintNativeEvent)
	int32 GetSpellPoints();

	UFUNCTION(BlueprintNativeEvent)
	void AddTalentPoints(int32 InPoints);

	UFUNCTION(BlueprintNativeEvent)
	void AddSpellPoints(int32 InPoints);


	
};
