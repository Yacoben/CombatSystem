// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/Attributes.h"

// Sets default values for this component's properties
UAttributes::UAttributes()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAttributes::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAttributes::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float UAttributes::GetHealthPercent()
{
	return Health / MaxHealth;
}

bool UAttributes::IsAlive()
{
	return Health > 0.f;
}

float UAttributes::GetStaminaPercent()
{
	return Stamina / MaxStamina;
}

void UAttributes::ReceiveDamage(float Damage)
{
	Health = FMath::Clamp(Health - Damage, 0.f, MaxHealth);

	UE_LOG(LogTemp, Warning, TEXT("Current Health: %f"), Health);
}

void UAttributes::ReduceStamina(float Energy)
{
	Stamina = FMath::Clamp(Stamina - Energy, 0.f, MaxStamina);

	UE_LOG(LogTemp, Warning, TEXT("Current Stamina: %f"), Stamina);
}

