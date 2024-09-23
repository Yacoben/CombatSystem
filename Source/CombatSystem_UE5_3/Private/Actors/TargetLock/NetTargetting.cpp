// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/TargetLock/NetTargetting.h"
#include "Components/SphereComponent.h"
#include "Interfaces/TargettingInterface.h"

ANetTargetting::ANetTargetting()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	SetRootComponent(SphereComponent);

	SphereComponent->SetSphereRadius(TargettingRadius);
}

void ANetTargetting::BeginPlay()
{
	Super::BeginPlay();
	
}

void ANetTargetting::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TArray<AActor*> ANetTargetting::GetTargetsInRange()
{
	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors, AActor::StaticClass());
	TArray<AActor*> ActorsInRange;

	for (AActor* Actor : OverlappingActors)
	{
		// Checking which Actors are overlapping
		//UE_LOG(LogTemp, Warning, TEXT("GetOverlappingActors: %s"), *Actor->GetName());

		if (Actor->Implements<UTargettingInterface>())
		{
			if (ITargettingInterface::Execute_IsTargettable(Actor))
			{
				ActorsInRange.AddUnique(Actor);
				// Checking which Actors with Interface Function are overlapping
				UE_LOG(LogTemp, Warning, TEXT("GetOverlappingActors: %s"), *Actor->GetName());
			}
		}
	}
	if (OverlappingActors.IsEmpty()) return TArray<AActor*>();

	return ActorsInRange;
}

