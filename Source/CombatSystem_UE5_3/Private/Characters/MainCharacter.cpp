

#include "Characters/MainCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Weapons/Weapon.h"

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

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(CharacterMappingContext, 0);
		}
	}
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

}

void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMainCharacter::Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &AMainCharacter::MoveCompleted);
		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMainCharacter::Look);
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMainCharacter::Jump);
		// SwitchGait
		EnhancedInputComponent->BindAction(SwitchGaitAction, ETriggerEvent::Started, this, &AMainCharacter::SwitchGait);
		// Roll
		EnhancedInputComponent->BindAction(RollAction, ETriggerEvent::Started, this, &AMainCharacter::Roll);
	}
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

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisValue.X);
		AddControllerPitchInput(LookAxisValue.Y);
	}
}

void AMainCharacter::SwitchGait(const FInputActionValue& Value)
{
	if (GaitState == EGaitState::EGS_Running)
	{
		GaitState = EGaitState::EGS_Walking;
		UpdateGait(GaitState);
	}
	else
	{
		GaitState = EGaitState::EGS_Running;
		UpdateGait(GaitState);
	}
}

void AMainCharacter::Roll(const FInputActionValue& Value)
{
	if (ActionState == EActionState::EAS_Unoccupied)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

		AnimInstance->Montage_Play(RollMontage);
		
		ActionState = EActionState::EAS_Rolling;
	}
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

void AMainCharacter::SpawnWeaponInHandSocket()
{
	if (GetWorld() && WeaponClass)
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AWeapon* ActiveWeapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass, GetActorLocation(), GetActorRotation(), SpawnParameters);

		FAttachmentTransformRules TransformRules = FAttachmentTransformRules::SnapToTargetIncludingScale;
		ActiveWeapon->AttachToComponent(GetMesh(), TransformRules, WeaponHandSocket);

		CharacterState = ECharacterState::ECS_Armed;
	}
}

