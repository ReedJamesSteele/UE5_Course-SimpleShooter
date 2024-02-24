// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickUpBase.h"
#include "AmmoPickUp.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AAmmoPickUp : public APickUpBase
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AAmmoPickUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	virtual void OnPickUp() override;

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* AmmoPickUpRootComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* AmmoPickUpMeshComponent;
	
};
