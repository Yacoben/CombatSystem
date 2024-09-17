// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/CharacterEnum.h"
#include "ComboInputs.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct COMBATSYSTEM_UE5_3_API FComboInputs : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	TArray<EComboInputs> ComboInputs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	TArray<UAnimMontage*> AttackMontages;

	FComboInputs();
	~FComboInputs();
};
