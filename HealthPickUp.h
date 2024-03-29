// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickUpBase.h"
#include "HealthPickUp.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AHealthPickUp : public APickUpBase
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AHealthPickUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual void OnPickUp();

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* HealthPickUpRootComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* HealthPickUpMeshComponent;
	
};
