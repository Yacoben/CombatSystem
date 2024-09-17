// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GaitSettings.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct COMBATSYSTEM_UE5_3_API FGaitSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gait Settings")
	float MaxWalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gait Settings")
	float MaxAcceleration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gait Settings")
	float BrakingDeceleration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gait Settings")
	float BrakingFrictionFactor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gait Settings")
	bool UseSeperateBrakingFriction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gait Settings")
	float BrakingFriction;

	FGaitSettings();
	~FGaitSettings();
};

USTRUCT(BlueprintType)
struct COMBATSYSTEM_UE5_3_API FLocomotionDirectionSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Locomotion Direction Settings")
	float ForwardMin = -35.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Locomotion Direction Settings")
	float ForwardMax = 35.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Locomotion Direction Settings")
	float BackwardMin = -145.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Locomotion Direction Settings")
	float BackwardMax = 145.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Locomotion Direction Settings")
	float DiagonalLeftMin = -140.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Locomotion Direction Settings")
	float DiagonalLeftMax = -40.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Locomotion Direction Settings")
	float DiagonalRightMin = 40.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Locomotion Direction Settings")
	float DiagonalRightMax = 140.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Locomotion Direction Settings")
	float Deadzone = 20.f;

	FLocomotionDirectionSettings();
	~FLocomotionDirectionSettings();
};
