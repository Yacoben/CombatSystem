// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/TargetLock/Targetter.h"
#include "Components/SceneComponent.h"
#include "Components/ArrowComponent.h"

ATargetter::ATargetter()
{
	PrimaryActorTick.bCanEverTick = true;


	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	SetRootComponent(SceneComponent);

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Component"));
	ArrowComponent->SetupAttachment(GetRootComponent());
	ArrowComponent->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));

}

void ATargetter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATargetter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

