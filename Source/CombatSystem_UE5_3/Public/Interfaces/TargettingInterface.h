// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TargettingInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTargettingInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class COMBATSYSTEM_UE5_3_API ITargettingInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool IsTargettable();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool IsTargetDead();
};
