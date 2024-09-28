// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RollSettings.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct COMBATSYSTEM_UE5_3_API FRollSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roll Direction Settings")
	float FMin = -22.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roll Direction Settings")
	float FMax = 22.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roll Direction Settings")
	float BMin = -157.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roll Direction Settings")
	float BMax = 157.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roll Direction Settings")
	float LMin = -112.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roll Direction Settings")
	float LMax = -67.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roll Direction Settings")
	float RMin = 67.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roll Direction Settings")
	float RMax = 112.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roll Direction Settings")
	float FRMin = -22.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roll Direction Settings")
	float FRMax = 67.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roll Direction Settings")
	float FLMin = -67.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roll Direction Settings")
	float FLMax = -22.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roll Direction Settings")
	float BRMin = 112.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roll Direction Settings")
	float BRMax = 157.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roll Direction Settings")
	float BLMin = -157.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roll Direction Settings")
	float BLMax = -112.5f;

	FRollSettings();
	~FRollSettings();
};
