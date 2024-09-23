

#include "Characters/BaseCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Weapons/Weapon.h"
#include "ActorComponents/Attributes.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	Attributes = CreateDefaultSubobject<UAttributes>(TEXT("Attributes"));
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseCharacter::SetWeaponCollisionEnabled(ECollisionEnabled::Type CollisionEnabled)
{
	if (ActiveWeapon && ActiveWeapon->GetWeaponBox())
	{
		ActiveWeapon->GetWeaponBox()->SetCollisionEnabled(CollisionEnabled);
		ActiveWeapon->IgnoreActors.Empty();
	}
}

void ABaseCharacter::HandleDamage(float DamageAmount)
{
	if (Attributes == nullptr) return;

	if (Attributes->IsAlive())
	{
		Attributes->ReceiveDamage(DamageAmount);
	}
}

bool ABaseCharacter::IsAlive()
{
	return Attributes && Attributes->IsAlive();
}


