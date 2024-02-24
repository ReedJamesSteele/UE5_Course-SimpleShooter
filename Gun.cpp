// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"
#include "ShooterCharacter.h"
#include "ShooterAIController.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	GunRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(GunRootComponent);

	GunMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	GunMeshComponent->SetupAttachment(GunRootComponent);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AGun::GunTrace(FHitResult& HitResultOut, FVector& ShotDirectionOut)
{
	AController* OwnerController{GetOwnerController()};
	if(OwnerController == nullptr) 
	{
		return false;
	}
	FVector ControllerLocation;//Out Param vvv
	FRotator ControllerRotation;//Out Param vvv
	OwnerController->GetPlayerViewPoint(ControllerLocation, ControllerRotation);
	ShotDirectionOut = -ControllerRotation.Vector();
	FVector BulletEnd = ControllerLocation + (ControllerRotation.Vector() * MaxRange);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	return GetWorld()->LineTraceSingleByChannel(HitResultOut, ControllerLocation, BulletEnd, ECC_GameTraceChannel1, Params); //Note: See if we can fix hitting behind pawn
}

AController* AGun::GetOwnerController() const
{
    APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if(OwnerPawn == nullptr)
	{
		return nullptr;
	}
	return OwnerPawn->GetController();

}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, GunMeshComponent, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, GunMeshComponent, TEXT("MuzzleFlashSocket"));

	FHitResult HitResult;
	FVector ShotDirection;

	bool bSuccess{GunTrace(HitResult, ShotDirection)};
	if(bSuccess)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactFlash, HitResult.Location, ShotDirection.Rotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, HitResult.Location, ShotDirection.Rotation());
		AActor* HitActor{HitResult.GetActor()};
		if(HitActor != nullptr)
		{
			//See if we can refactor this vvv
			AShooterCharacter* HitActorIsShooter{Cast<AShooterCharacter>(HitActor)};
			if(HitActorIsShooter != nullptr)
			{
				AShooterAIController* HitActorIsAI{Cast<AShooterAIController>(HitActorIsShooter->GetController())};
				if(HitActorIsAI != nullptr)
				{
					UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitConfirm, GetActorLocation(), ShotDirection.Rotation());
				}
			}

			FPointDamageEvent DamageEvent(Damage, HitResult, ShotDirection, nullptr);
			AController* OwnerController{GetOwnerController()};
			HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);

		}
		//DrawDebugPoint(GetWorld(), HitResult.Location, 20.f, FColor::Red, true);
	}
	//UE_LOG(LogTemp, Warning, TEXT("You've been shot!"));
}

