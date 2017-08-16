// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"





/**
 * 
 */
UCLASS()
class TANKGAME_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:

	void Tick(float DeltaTime) override;
	void BeginPlay() override;
	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION()
	void OnTankDeath();

protected:

	//How close can the AI tank get to the player.
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 8000.f; //80 meters default

	
	
};
