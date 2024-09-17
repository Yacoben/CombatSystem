// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Weapon.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	/* Creating subobjects components */
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	SetRootComponent(StaticMeshComponent);
	/* Creating subobjects components */

	StaticMeshComponent->SetGenerateOverlapEvents(true);

	/* Collision preset */
	StaticMeshComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StaticMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	StaticMeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	StaticMeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
	/* Collision preset */
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();

}

void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

