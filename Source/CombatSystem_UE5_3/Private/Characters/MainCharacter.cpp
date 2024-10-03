

#include "Characters/MainCharacter.h"

/* Components */
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
/* Components */

/* Enhanced Input */
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputCoreTypes.h"
/* Enhanced Input */

/* Weapons */
#include "Weapons/Weapon.h"
/* Weapons */

/* Actors */
#include "Actors/TargetLock/NetTargetting.h"
#include "Actors/TargetLock/Targetter.h"
/* Actors */

/* Interfaces */
#include "Interfaces/TargettingInterface.h"
/* Interfaces */

#include "Kismet/KismetMathLibrary.h"

AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	/* Creating subobjects components */
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	/* Creating subobjects components */

	/* Controller Rotation preset */
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	/* Controller Rotation preset */

	/* Character Movement preset */
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	/* Character Movement preset */

	/* CharacterMesh preset */
	GetMesh()->SetGenerateOverlapEvents(true);
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -92.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, 0.f, -90.f));
	/* CharacterMesh preset */

	/* Capsule preset */
	GetCapsuleComponent()->SetCapsuleHalfHeight(92.f);
	/* Capsule preset */

	/* SpringArm preset */
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->TargetArmLength = 300.f;
	/* SpringArm preset */

	/* Camera preset */
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;
	/* Camera preset */

	/* Collision preset */
	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	GetMesh()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);

	GetCapsuleComponent()->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
	/* Collision preset */
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	SwitchMappingContext(KeyboardMappingContext);
	UpdateGait(GaitState);
	UpdateInputData(SideInput, ForwardInput, InputLocomotionDirection);
	SpawnWeaponInHandSocket();

	if (GetController())
	{
		if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
		{
			AnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &AMainCharacter::OnNotifyBegin);
			AnimInstance->OnMontageEnded.AddDynamic(this, &AMainCharacter::OnMontageEnding);
		}
	}
}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsTargetting)
	{
		CheckTargetting();
		CharacterLock(DeltaTime, InterpTargetLock);
	}
}

void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMainCharacter::Look);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Started, this, &AMainCharacter::LookStarted);
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMainCharacter::Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &AMainCharacter::MoveCompleted);
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMainCharacter::Jump);
		// SwitchGait
		EnhancedInputComponent->BindAction(SwitchGaitAction, ETriggerEvent::Started, this, &AMainCharacter::SwitchGait);
		// Roll
		EnhancedInputComponent->BindAction(RollAction, ETriggerEvent::Started, this, &AMainCharacter::Roll);
		// TargetLock
		EnhancedInputComponent->BindAction(TargetLockAction, ETriggerEvent::Started, this, &AMainCharacter::TargetLock);
		EnhancedInputComponent->BindAction(ChangeTargetLockAction, ETriggerEvent::Started, this, &AMainCharacter::ChangeTargetLock);
		// Sprint
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &AMainCharacter::Sprint);
		// Switch Mapping Context
		EnhancedInputComponent->BindAction(SwitchMappingAction, ETriggerEvent::Started, this, &AMainCharacter::SwitchMapping);
	}
}

void AMainCharacter::SwitchMapping(const FInputActionValue& Value)
{
	if (HasMappingContext(KeyboardMappingContext))
	{
		SwitchMappingContext(GamepadMappingContext);
	}
	else
	{
		SwitchMappingContext(KeyboardMappingContext);
	}
}

void AMainCharacter::SwitchMappingContext(UInputMappingContext* MappingContext)
{
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(MappingContext, 0);
		}
	}
}

bool AMainCharacter::HasMappingContext(const UInputMappingContext* MappingContext)
{
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			return Subsystem->HasMappingContext(MappingContext);
		}
	}
	return false;
}

void AMainCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MoveAxisValue = Value.Get<FVector2D>();
	InputLocomotionDirection = MoveAxisValue;

	if (Controller != nullptr)
	{
		// Which way is forward
		const FRotator ControlRotation = GetControlRotation();
		const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);

		// Get Forward Vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// Get Right Vector
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		SideInput = InputLocomotionDirection.X;
		ForwardInput = InputLocomotionDirection.Y;

		// Add Movement
		AddMovementInput(RightDirection, SideInput);
		AddMovementInput(ForwardDirection, ForwardInput);

		UpdateInputData(SideInput, ForwardInput, InputLocomotionDirection);
	}
}

void AMainCharacter::MoveCompleted(const FInputActionValue& Value)
{
	SideInput = 0.f;
	ForwardInput = 0.f;
	UpdateInputData(SideInput, ForwardInput, InputLocomotionDirection);
}

void AMainCharacter::Look(const FInputActionValue& Value)
{	
	const FVector2D LookAxisValue = Value.Get<FVector2D>();

	if (!bIsTargetting)
	{
		if (Controller != nullptr)
		{
			AddControllerYawInput(LookAxisValue.X);
			AddControllerPitchInput(LookAxisValue.Y);
		}
	}
}

void AMainCharacter::LookStarted(const FInputActionValue& Value)
{
	if (HasMappingContext(GamepadMappingContext) && bIsTargetting)
	{
		ChangeTargetLock(Value);
	}
}

void AMainCharacter::SwitchGait(const FInputActionValue& Value)
{
	if (InputValueMultiplier != 1.f)
	{
		InputValueMultiplier = 1.f;
	}
	else
	{
		InputValueMultiplier = 2.f;
	}
}

void AMainCharacter::Roll(const FInputActionValue& Value)
{
	if (ActionState == EActionState::EAS_Unoccupied)
	{
		if (IsSprinting()) InputValueMultiplier = 2.f;

		PlayMontageRoll(1.4f);
		ActionState = EActionState::EAS_Rolling;
	};
};

void AMainCharacter::TargetLock(const FInputActionValue& Value)
{
	if (bIsTargetting == false)
	{
		ClearNet();
		SpawnTargettingNet();

		if (TargetsInRange.Num() > 0)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Closest Target: %s"), *ClosestTarget->GetName());

			GetClosestTarget(TargetsInRange);
			ClearNet();
			ClearTargetter();
			SpawnTargetter();
			AttachTargetter(ClosestTarget);
			bIsTargetting = true;
		}
		else
		{
			StopTargetting();
		}
	}
	else
	{
		StopTargetting();
	}
}

void AMainCharacter::Sprint(const FInputActionValue& Value)
{
	if (IsSprinting())
	{
		InputValueMultiplier = 2.f;
		bIsSprinting = false;
	}
	else
	{
		bIsSprinting = true;
		InputValueMultiplier = 3.f;
		StopTargetting();
	}
}

void AMainCharacter::ChangeTargetLock(const FInputActionValue& Value)
{
	if (TargetsInRange.Num() == 0) return;

	float ClosestDistance = 2000.f;
	TArray<AActor*> OtherTargets;

	if (bIsTargetting)
	{
		ClearNet();
		SpawnTargettingNet();

		for (AActor* Target : TargetsInRange)
		{
			if (Target != ClosestTarget)
			{
				OtherTargets.AddUnique(Target);
			}
		}
		GetClosestTarget(OtherTargets);
		ClearNet();
		ClearTargetter();
		SpawnTargetter();
		AttachTargetter(ClosestTarget);
	}
}

bool AMainCharacter::CanLook()
{
	return !bIsTargetting;
}

bool AMainCharacter::IsSprinting()
{
	return InputValueMultiplier == 3.f && bIsSprinting == true;
}

void AMainCharacter::OnNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPayload)
{
}

void AMainCharacter::OnMontageEnding(UAnimMontage* AnimMontage, bool bInterrupted)
{
	if (!bInterrupted)
	{
		NextAttack = false;
		AttackIndex = 0;
	}
}

void AMainCharacter::SetActionState(EActionState Action)
{
	ActionState = Action;
}

float AMainCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	HandleDamage(DamageAmount);

	return DamageAmount;
}

void AMainCharacter::SpawnWeaponInHandSocket()
{
	if (GetWorld() && WeaponClass)
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		ActiveWeapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass, GetActorLocation(), GetActorRotation(), SpawnParameters);

		FAttachmentTransformRules TransformRules = FAttachmentTransformRules::SnapToTargetIncludingScale;
		ActiveWeapon->AttachToComponent(GetMesh(), TransformRules, WeaponHandSocket);

		CharacterState = ECharacterState::ECS_Armed;
	}
}
/* 
*/
/* Target Lock */
TArray<AActor*> AMainCharacter::SpawnTargettingNet()
{
	if (GetWorld() == nullptr) return TArray<AActor*>();

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	Net = GetWorld()->SpawnActor<ANetTargetting>(NetTargetClass, GetActorLocation(), GetActorRotation(), SpawnParameters);
	TargetsInRange = Net->GetTargetsInRange();
	return TargetsInRange;
}

void AMainCharacter::ClearNet()
{
	if (Net)
	{
		Net->Destroy();
	}
}

AActor* AMainCharacter::GetClosestTarget(TArray<AActor*> TargetsInRadius)
{
	float ClosestDistance = 2000.f;

	for (AActor* Target : TargetsInRadius)
	{
		if (GetDistanceTo(Target) < ClosestDistance)
		{
			ClosestDistance = GetDistanceTo(Target);
			ClosestTarget = Target;
			UE_LOG(LogTemp, Warning, TEXT("Distance: %f"), ClosestDistance);
			UE_LOG(LogTemp, Warning, TEXT("Closest Target: %s"), *ClosestTarget->GetName());
		}
	}
	return ClosestTarget;
}

AActor* AMainCharacter::SpawnTargetter()
{
	if (GetWorld() == nullptr) return nullptr;
	if (ClosestTarget == nullptr) return nullptr;

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	Targetter = GetWorld()->SpawnActor<ATargetter>(TargetterClass, ClosestTarget->GetActorLocation(), ClosestTarget->GetActorRotation(), SpawnParameters);

	return Targetter;
}

void AMainCharacter::AttachTargetter(AActor* Target)
{
	if (Target == nullptr) return;

	FAttachmentTransformRules TransformRules = FAttachmentTransformRules::KeepWorldTransform;
	TransformRules.LocationRule = EAttachmentRule::KeepWorld;
	TransformRules.RotationRule = EAttachmentRule::KeepWorld;
	TransformRules.ScaleRule = EAttachmentRule::KeepWorld;

	Targetter->AttachToActor(Target, TransformRules);
}

void AMainCharacter::ClearTargetter()
{
	if (Targetter)
	{
		Targetter->Destroy();
	}
}

void AMainCharacter::CharacterLock(float DeltaTime, float InterpSpeed)
{
	if (ClosestTarget && bIsTargetting == true)
	{
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetController()->GetPawn()->GetActorLocation(), ClosestTarget->GetActorLocation());
		FRotator InterpLookAtRotation = UKismetMathLibrary::RInterpTo(GetControlRotation(), LookAtRotation, DeltaTime, InterpSpeed);

		GetController()->SetControlRotation(InterpLookAtRotation);
		GetCharacterMovement()->bOrientRotationToMovement = false;
	}
}

void AMainCharacter::CheckTargetting()
{
	if (ClosestTarget == nullptr) return;

	if (!IsClosestTargetDead() && GetDistanceTo(ClosestTarget) > 2000.f)
	{
		//RemoveWarpClosestTarget()
		StopTargetting();
	}
	else if (IsClosestTargetDead())
	{
		//RemoveWarpClosestTarget
		StopTargetting();
		//OnTargetDeath.Broadcast()
	}
	else if (!IsClosestTargetDead() && ActionState == EActionState::EAS_Attacking)
	{
		if (GetDistanceTo(ClosestTarget) <= 200.f)
		{
			//Update Warp()
		}
		else
		{
			//RemoveWarpClosestTarget()
		}
	}
}

void AMainCharacter::StopTargetting()
{
	ClearNet();
	ClearTargetter();
	ClosestTarget = nullptr;
	bIsTargetting = false;
	TargetsInRange.Empty();
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

bool AMainCharacter::IsClosestTargetDead()
{
	if (ClosestTarget && ClosestTarget->Implements<UTargettingInterface>())
	{
		if (ITargettingInterface::Execute_IsTargetDead(ClosestTarget))
		{
			return ITargettingInterface::Execute_IsTargetDead(ClosestTarget);
		}
	}
	return false;
}

void AMainCharacter::OnClosestTargetIsDead()
{
	ClearNet();
	SpawnTargettingNet();

	if (TargetsInRange.Num() > 0)
	{
		GetClosestTarget(TargetsInRange);
		ClearNet();
		ClearTargetter();
		SpawnTargetter();
		AttachTargetter(ClosestTarget);
		bIsTargetting = true;
	}
	else
	{
		StopTargetting();
	}
}
/*
*/
/* Target Lock */
