// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void GameHasEnded(AActor *EndGameFocus, bool bIsWinner) override;

private: 
	//HUD
	UPROPERTY(EditAnywhere)
	class TSubclassOf<UUserWidget> LoseScreenClass;
	UPROPERTY(EditAnywhere)
	class TSubclassOf<UUserWidget> WinScreenClass;
	UPROPERTY(EditAnywhere)
	class TSubclassOf<UUserWidget> HUDClass;

	UPROPERTY(EditAnywhere)
	float RestartDelay{5.f};

	FTimerHandle RestartTimer;

	UPROPERTY(EditAnywhere)
	UUserWidget* HUD;
};
