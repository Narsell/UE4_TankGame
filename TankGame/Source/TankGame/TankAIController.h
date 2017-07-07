// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;
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

private:

	ATank* GetControlledAITank() const;
	ATank* GetPlayerTank() const;


	
	
};
