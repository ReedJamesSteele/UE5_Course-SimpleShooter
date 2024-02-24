// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAIController.generated.h"



/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AShooterAIController : public AAIController
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterAIController();

	virtual void Tick(float DeltaTime) override;
	bool IsDead() const;


protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "AI")
	class UBehaviorTree* AIBehavior;
	//{

	//}

	//Revisit Patrol routes...better in BP?
	//UPROPERTY(EditAnywhere, Category = "AI")
	//FVector RouteOffset{0.f, 1000.f, 0.f};


	
	
};
