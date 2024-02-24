// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gun.h"
#include "Launcher.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API ALauncher : public AGun
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ALauncher();

	virtual void PullTrigger() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	//UPROPERTY(VisibleAnywhere)
	//USceneComponent* LauncherRootComponent;

	//UPROPERTY(VisibleAnywhere)
	//USkeletalMeshComponent* LauncherMeshComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Ammo Type")
	TSubclassOf<class AGrenade> GrenadeClass;

	class AGrenade* Grenade;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"));
	USceneComponent* GrenadeSpawnPoint;
	
};
