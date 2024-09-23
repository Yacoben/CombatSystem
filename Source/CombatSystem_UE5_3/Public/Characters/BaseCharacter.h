
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/HitInterface.h"
#include "BaseCharacter.generated.h"

UCLASS()
class COMBATSYSTEM_UE5_3_API ABaseCharacter : public ACharacter, public IHitInterface
{
	GENERATED_BODY()

public:
	ABaseCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;


public:
	UFUNCTION(BlueprintCallable)
	void SetWeaponCollisionEnabled(ECollisionEnabled::Type CollisionEnabled);

protected:
	void HandleDamage(float Damage);
	bool IsAlive();

	/* Animation Montages */
	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* AttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* DirectionalHitReactMontage;

	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* HitReactMontage;

	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* DeathMontage;
	/* Animation Montages */

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Weapon)
	class AWeapon* ActiveWeapon;

	/* Actor Components */
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UAttributes> Attributes;
	/* Actor Components */

private:

};
