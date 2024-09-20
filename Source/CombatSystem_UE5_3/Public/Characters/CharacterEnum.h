#pragma once

UENUM(BlueprintType)
enum class ELocomotionDirection : uint8
{
	ELD_Forward UMETA(DisplayName = "Forward"),
	ELD_Backward UMETA(DisplayName = "Backward"),
	ELD_Right UMETA(DisplayName = "Right"),
	ELD_Left UMETA(DisplayName = "Left"),
	ELD_ForwardRight UMETA(DisplayName = "ForwardRight"),
	ELD_ForwardLeft UMETA(DisplayName = "ForwardLeft"),
	ELD_BackwardRight UMETA(DisplayName = "BackwardRight"),
	ELD_BackwardLeft UMETA(DisplayName = "BackwardLeft")

};

UENUM(BlueprintType)
enum class EGaitState : uint8
{
	EGS_Walking UMETA(DisplayName = "Walking"),
	EGS_Running UMETA(DisplayName = "Running")
};

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	ECS_Unarmed UMETA(DisplayName = "Unarmed"),
	ECS_Armed UMETA(DisplayName = "Armed")
};

UENUM(BlueprintType)
enum class EActionState : uint8
{
	EAS_Unoccupied UMETA(DisplayName = "Unoccupied"),
	EAS_Attacking UMETA(DisplayName = "Attacking"),
	EAS_HitReact UMETA(DisplayName = "Hit React"),
	EAS_Rolling UMETA(DisplayName = "Rolling")
};

UENUM(BlueprintType)
enum class EComboInputs : uint8
{
	ECI_None UMETA(DisplayName = "None"),
	ECI_LightAttack UMETA(DisplayName = "LightAttack"),
	ECI_HeavyAttack UMETA(DisplayName = "HeavyAttack")
};
