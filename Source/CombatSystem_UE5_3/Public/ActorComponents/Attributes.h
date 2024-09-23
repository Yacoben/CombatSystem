// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Attributes.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COMBATSYSTEM_UE5_3_API UAttributes : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttributes();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


/* My Variables*/

public:
	float GetHealthPercent();
	bool IsAlive();
	float GetStaminaPercent();
	void ReceiveDamage(float Damage);
	void ReduceStamina(float Energy);

protected:

private:
	UPROPERTY(EditAnywhere, Category = "Attributes")
	float Health = 100.f;

	UPROPERTY(EditAnywhere, Category = "Attributes")
	float MaxHealth = 100.f;

	UPROPERTY(EditAnywhere, Category = "Attributes")
	float Stamina = 100.f;

	UPROPERTY(EditAnywhere, Category = "Attributes")
	float MaxStamina = 100.f;


		
};
