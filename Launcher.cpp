// Fill out your copyright notice in the Description page of Project Settings.


#include "Launcher.h"
#include "Grenade.h"

ALauncher::ALauncher()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    //LauncherRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	//SetRootComponent(LauncherRootComponent);

	//LauncherMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	//LauncherMeshComponent->SetupAttachment(LauncherRootComponent);

    GrenadeSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Grenade Spawn Point"));
    GrenadeSpawnPoint->SetupAttachment(GunMeshComponent);
}

void ALauncher::PullTrigger()
{
    UE_LOG(LogTemp, Warning, TEXT("You're shooting the launcher!'"));
    FVector GrenadeLocation = GrenadeSpawnPoint->GetComponentLocation();
    FRotator GrenadeRotation = GrenadeSpawnPoint->GetComponentRotation();
    GetWorld()->SpawnActor<AGrenade>(GrenadeClass, GrenadeLocation, GrenadeRotation);
}

// Called when the game starts or when spawned
void ALauncher::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALauncher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

