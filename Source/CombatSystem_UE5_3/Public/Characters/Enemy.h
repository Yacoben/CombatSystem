// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "Characters/EnemyEnum.h"
#include "Interfaces/TargettingInterface.h"
#include "Enemy.generated.h"

/**
 * 
 */
UCLASS()
class COMBATSYSTEM_UE5_3_API AEnemy : public ABaseCharacter, public ITargettingInterface
{
	GENERATED_BODY()

public:
	AEnemy();

	/* <AActor> */
	virtual void Tick(float DeltaTime) override;
	/* <AActor> */

protected:
	/* <AActor> */
	virtual void BeginPlay() override;
	/* <AActor> */

public:
	/* <AActor> */
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	/* <AActor> */

	/* <IHitInterface> */
	virtual void GetHit_Implementation(const FVector& ImpactPoint, AWeapon* DamageCauser, AActor* Hitter) override;
	/* <IHitInterface> */

	/* <ITargettingInterface> */
	virtual bool IsTargettable_Implementation() override;
	virtual bool IsTargetDead_Implementation() override;
	/* <ITargettingInterface> */

protected:
	/* Enums */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EEnemyGait EnemyGait = EEnemyGait::EEG_Walking;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EEnemyState EnemyState = EEnemyState::EES_Unarmed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EEnemyAction EnemyAction = EEnemyAction::EEA_Unoccupied;
	/* Enums */

private:
	UFUNCTION(BlueprintPure)
	bool bIsDead();
	

};
