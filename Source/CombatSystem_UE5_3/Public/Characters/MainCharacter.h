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

	UFUNCTION(BlueprintImplementableEvent, Category = Input)
	void UpdateInputData(float InputSide, float InputForward, FVector2D LocomotionDirectionValue);

private:
	/* Enhanced Input System */
	void Move(const FInputActionValue& Value);
	void MoveCompleted(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void SwitchGait(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputMappingContext* CharacterMappingContext;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* MoveAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	FVector2D InputLocomotionDirection;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	float SideInput;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	float ForwardInput;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* SwitchGaitAction;
	/* Enhanced Input System */

	/* AnimMontage */
	UFUNCTION()
	void OnNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPayload);

	UFUNCTION()
	void OnMontageEnding(UAnimMontage* AnimMontage, bool bInterrupted);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack, meta = (AllowPrivateAccess = "true"))
	TArray<UAnimMontage*> LightAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack, meta = (AllowPrivateAccess = "true"))
	TArray<UAnimMontage*> HeavyAttackMontage;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Attack, meta = (AllowPrivateAccess = "true"))
	int32 AttackIndex = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Attack, meta = (AllowPrivateAccess = "true"))
	bool NextAttack = false;
	/* AnimMontage */

public:

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = Locomotion)
	void UpdateGait(EGaitState DesiredGait);

	void SpawnWeaponInHandSocket();

	/* Enums */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	ECharacterState CharacterState;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EGaitState GaitState = EGaitState::EGS_Running;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EActionState ActionState = EActionState::EAS_Unoccupied;
	/* Enums */

private:
	
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

};
