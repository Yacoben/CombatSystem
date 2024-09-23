// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NetTargetting.generated.h"

UCLASS()
class COMBATSYSTEM_UE5_3_API ANetTargetting : public AActor
{
	GENERATED_BODY()
	
public:	
	ANetTargetting();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:

	UFUNCTION()
	TArray<AActor*> GetTargetsInRange();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float TargettingRadius = 2000.f;


protected:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class USphereComponent> SphereComponent;

private:

};
