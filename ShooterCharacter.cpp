// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Gun.h"
#include "Components/CapsuleComponent.h"
#include "SimpleShooterGameModeBase.h"
#include "AmmoPickUp.h"



// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	Ammo = MaxAmmo;
	
	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Get the player controller
    auto playerController = Cast<APlayerController>(GetController());
 
    // Get the local player enhanced input subsystem
    auto eiSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());
    //Add the input mapping context
    eiSubsystem->AddMappingContext(inputMapping, 0);
 
    // Get the EnhancedInputComponent
    auto playerEIcomponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	//Bind Move() to the mapping
	//BindAction for enhanced system takes Action, ETriggerEvent, object, and function
	//ETriggerEvent is an enum, where Triggered means "button is held down".
	playerEIcomponent->BindAction(inputWalk, ETriggerEvent::Triggered, this, &AShooterCharacter::Walk);
    playerEIcomponent->BindAction(inputStrafe, ETriggerEvent::Triggered, this, &AShooterCharacter::Strafe);
   	playerEIcomponent->BindAction(inputTurn, ETriggerEvent::Triggered, this, &AShooterCharacter::Turn);
	playerEIcomponent->BindAction(inputLookUpAndDown, ETriggerEvent::Triggered, this, &AShooterCharacter::LookUpAndDown);
    playerEIcomponent->BindAction(inputJump, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	playerEIcomponent->BindAction(inputShoot, ETriggerEvent::Triggered, this, &AShooterCharacter::Shoot);
	playerEIcomponent->BindAction(inputAim, ETriggerEvent::Triggered, this, &AShooterCharacter::Aim);

}

void AShooterCharacter::Walk(const FInputActionValue & AxisValue)
{
	AddMovementInput(GetActorForwardVector() * (AxisValue.Get<float>()));
}

void AShooterCharacter::Strafe(const FInputActionValue & AxisValue)
{
	AddMovementInput(GetActorRightVector() * (AxisValue.Get<float>()));
}

void AShooterCharacter::Turn(const FInputActionValue & AxisValue)
{
	AddControllerYawInput((AxisValue.Get<float>()) * LookSensitivity * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::LookUpAndDown(const FInputActionValue & AxisValue)
{
	AddControllerPitchInput((AxisValue.Get<float>()) * LookSensitivity * GetWorld()->GetDeltaSeconds());
}

bool AShooterCharacter::OutOfAmmo() const
{
	return Ammo <= 0;
}

void AShooterCharacter::Shoot()
{
	if(!OutOfAmmo())
	{
		Gun->PullTrigger();
		Ammo -= 1;
	}
}

void AShooterCharacter::Aim()
{
	UE_LOG(LogTemp, Display, TEXT("Aiming"));
}

float AShooterCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply{Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser)};
	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;
	UE_LOG(LogTemp, Warning, TEXT("Health - %f" ), Health);

	if(IsDead())
	{
		ASimpleShooterGameModeBase* GameMode{GetWorld()->GetAuthGameMode<ASimpleShooterGameModeBase>()};

		if(GameMode != nullptr)
		{
			GameMode->PawnKilled(this);
		}
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	return DamageToApply;
}

bool AShooterCharacter::IsDead() const
{
	return Health <= 0;
}

float AShooterCharacter::GetHealthPercent() const
{
    return Health / MaxHealth;
}

float AShooterCharacter::GetAmmoPercent() const
{
    return Ammo / MaxAmmo;
}

bool AShooterCharacter::GetAiming() const
{
	return bAiming;
}

bool AShooterCharacter::GetShooting() const
{
	return bShooting;
}

void AShooterCharacter::Reload()
{
	if(Ammo < MaxAmmo)
	{
		Ammo = MaxAmmo;
	}
}

void AShooterCharacter::Heal()
{
	if(Health < MaxHealth)
	{
		Health = MaxHealth;
	}
}