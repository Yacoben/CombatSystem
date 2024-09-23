#pragma once

UENUM(BlueprintType)
enum class EEnemyGait : uint8
{
	EEG_Walking UMETA(DisplayName = "Walking"),
	EEG_Running UMETA(DisplayName = "Running"),
};

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	EES_Unarmed UMETA(DisplayName = "Unarmed"),
	EES_Armed UMETA(DisplayName = "Armed")
};

UENUM(BlueprintType)
enum class EEnemyAction : uint8
{
	EEA_Unoccupied UMETA(DisplayName = "Unoccupied"),
	EEA_Dead UMETA(DisplayName = "Dead"),
	EEA_Patrolling UMETA(DisplayName = "Patrolling"),
	EEA_Chasing UMETA(DisplayName = "Chasing"),
	EEA_InCombat UMETA(DisplayName = "InCombat"),
	EEA_Attacking UMETA(DisplayName = "Attacking")
};
