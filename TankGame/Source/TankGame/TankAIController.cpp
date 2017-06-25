// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerTank = GetPlayerTank();

	if (PlayerTank)
		UE_LOG(LogTemp, Warning, TEXT("Tank AI Controller aiming at %s"), *(PlayerTank->GetName()))
	else
		UE_LOG(LogTemp, Warning, TEXT("Tank AI Controller not aiming"))

}


ATank* ATankAIController::GetControlledAITank() const
{
	
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!PlayerPawn)
		return nullptr;
	else
		return Cast<ATank>(PlayerPawn);
}

