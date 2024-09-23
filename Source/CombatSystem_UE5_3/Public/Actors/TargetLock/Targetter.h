// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Targetter.generated.h"

UCLASS()
class COMBATSYSTEM_UE5_3_API ATargetter : public AActor
{
	GENERATED_BODY()
	
public:	
	ATargetter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class USceneComponent> SceneComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UArrowComponent> ArrowComponent;
};
