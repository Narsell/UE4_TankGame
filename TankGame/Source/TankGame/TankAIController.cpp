// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"


ATank* ATankAIController::GetControlledAITank() const 
{
	
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	
	return 0;
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledAITank = GetControlledAITank();

	if(ControlledAITank)
		UE_LOG(LogTemp, Warning, TEXT("Tank AI Controller possessing: %s"), *(ControlledAITank->GetName()))
	else
		UE_LOG(LogTemp, Warning, TEXT("Tank AI Controller not possesing a tank actor"))

}
