// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoPickUp.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAmmoPickUp::AAmmoPickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	AmmoPickUpRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(AmmoPickUpRootComponent);

	AmmoPickUpMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	AmmoPickUpMeshComponent->SetupAttachment(AmmoPickUpRootComponent);
}

// Called when the game starts or when spawned
void AAmmoPickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAmmoPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAmmoPickUp::OnPickUp()
{
    Super::OnPickUp();
}

