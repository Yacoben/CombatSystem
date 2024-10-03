// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Characters/CharacterEnum.h"
#include "GaitSettings.h"
#include "MainCharacter.generated.h"

/**
 * 
 */
UCLASS()
class COMBATSYSTEM_UE5_3_API AMainCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AMainCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
	UFUNCTION(BlueprintImplementableEvent, Category = Input)
	void UpdateInputData(float InputSide, float InputForward, FVector2D LocomotionDirectionValue);

	UFUNCTION(BlueprintImplementableEvent, Category = Attack)
	void UpdateActionData(EActionState Action);

	UFUNCTION(BlueprintImplementableEvent, Category = Attack)
	void PlayMontageRoll(float PlayRate);

	/* <AActor> */
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	/* <AActor> */

protected:
	void SwitchMappingContext(class UInputMappingContext* MappingContext);
	bool HasMappingContext(const class UInputMappingContext* MappingContext);

	UFUNCTION(BlueprintImplementableEvent, Category = Locomotion)
	void UpdateGait(EGaitState DesiredGait);
	void SpawnWeaponInHandSocket();

	/* Target Lock */
	TArray<AActor*> SpawnTargettingNet();
	void ClearNet();
	AActor* GetClosestTarget(TArray<AActor*> TargetsInRadius);
	AActor* SpawnTargetter();
	void AttachTargetter(AActor* Target);
	void ClearTargetter();
	void CharacterLock(float DeltaTime, float InterpSpeed);
	void CheckTargetting();
	void StopTargetting();
	bool IsClosestTargetDead();
	void OnClosestTargetIsDead();

	UPROPERTY(BlueprintReadWrite)
	bool bIsTargetting = false;

	UPROPERTY(EditAnywhere, Category = Combat)
	float InterpTargetLock = 2.f;

	UPROPERTY(EditAnywhere, Category = Combat)
	TSubclassOf<class ANetTargetting> NetTargetClass;

	UPROPERTY(EditAnywhere, Category = Combat)
	TSubclassOf<class ATargetter> TargetterClass;

	// Net actor spawned in world
	UPROPERTY(BlueprintReadWrite)
	class ANetTargetting* Net;

	// Targetter actor spawned in world
	UPROPERTY(BlueprintReadWrite)
	class ATargetter* Targetter;

	UPROPERTY(BlueprintReadWrite)
	TArray<AActor*> TargetsInRange;

	UPROPERTY(BlueprintReadWrite)
	AActor* ClosestTarget;

	UPROPERTY(BlueprintReadWrite)
	AActor* SecondClosestTarget;
	/* Target Lock */

	/* Enums */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	ECharacterState CharacterState;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EGaitState GaitState = EGaitState::EGS_Running;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EActionState ActionState = EActionState::EAS_Unoccupied;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EComboInputs ComboInputs = EComboInputs::ECI_None;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	ERollDirection RollDirection;
	/* Enums */

private:
	/* Enhanced Input System */
	void SwitchMapping(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);
	void MoveCompleted(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void LookStarted(const FInputActionValue& Value);
	void SwitchGait(const FInputActionValue& Value);
	void Roll(const FInputActionValue& Value);
	void TargetLock(const FInputActionValue& Value);
	void Sprint(const FInputActionValue& Value);
	void ChangeTargetLock(const FInputActionValue& Value);
	/* Enhanced Input System */

	bool CanLook();

	bool bIsSprinting = false;

	UFUNCTION(BlueprintPure)
	bool IsSprinting();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	FVector2D InputLocomotionDirection;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	float SideInput;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	float ForwardInput;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	float MinSideInput = -3.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	float MaxSideInput = 3.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	float MinForwardInput = -3.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	float MaxForwardInput = 3.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	float InputValueMultiplier = 2.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	float SavedSideInput;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	float SavedForwardInput;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	float LocomotionAngle;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputMappingContext* KeyboardMappingContext;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputMappingContext* GamepadMappingContext;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* SwitchGaitAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* RollAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* TargetLockAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* ChangeTargetLockAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* SprintAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* SwitchMappingAction;
	/* Enhanced Input System */

	/* AnimMontage */
	UFUNCTION()
	void OnNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPayload);

	UFUNCTION()
	void OnMontageEnding(UAnimMontage* AnimMontage, bool bInterrupted);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Attack, meta = (AllowPrivateAccess = "true"))
	int32 AttackIndex = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Attack, meta = (AllowPrivateAccess = "true"))
	bool NextAttack = false;
	/* AnimMontage */

	/* Components */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> CameraComponent;

	/* Components */

	/* Weapon class */
	UPROPERTY(EditAnywhere, Category = Weapon)
	TSubclassOf<class AWeapon> WeaponClass;

	UPROPERTY(EditAnywhere, Category = Weapon)
	FName WeaponSocket;

	UPROPERTY(EditAnywhere, Category = Weapon)
	FName WeaponHandSocket;
	/* Weapon class */

	public:
		UFUNCTION(BlueprintCallable)
		FORCEINLINE void SetActionState(EActionState Action);

		UFUNCTION(BlueprintCallable)
		FORCEINLINE void SetNextAttack(bool Value) { NextAttack = Value; }

		UFUNCTION(BlueprintCallable)
		FORCEINLINE void SetAttackIndex(int32 Index) { AttackIndex = Index; }
};
