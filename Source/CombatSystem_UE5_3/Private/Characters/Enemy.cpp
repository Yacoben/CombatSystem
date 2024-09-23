// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemy.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ActorComponents/Attributes.h"

AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	Tags.Add(FName("Enemy"));
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	HandleDamage(DamageAmount);

	return DamageAmount;
}

void AEnemy::GetHit_Implementation(const FVector& ImpactPoint, AWeapon* DamageCauser, AActor* Hitter)
{
	if (IsAlive())
	{
		UE_LOG(LogTemp, Warning, TEXT("DOSTA£EM!"));
	}
	else
	{
		bIsDead();
		UE_LOG(LogTemp, Warning, TEXT("dead"));
	}
}

bool AEnemy::IsTargettable_Implementation()
{
	return true;
}

bool AEnemy::IsTargetDead_Implementation()
{
	return bIsDead();
}

bool AEnemy::bIsDead()
{
	return EnemyAction == EEnemyAction::EEA_Dead;
}

