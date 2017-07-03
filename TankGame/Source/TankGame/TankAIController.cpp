// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();



}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!GetPlayerTank() ) 
	{ 
		UE_LOG(LogTemp, Warning, TEXT("failed TankAIController.cpp line 18"))
		return; 
	}
	FVector HitLocation = GetPlayerTank()->GetActorLocation();
	GetControlledAITank()->AimAt(HitLocation);

}


ATank* ATankAIController::GetControlledAITank() const
{
	
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!PlayerPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("failed TankPlayerController.cpp line 40"))
		return nullptr;
	}
	else
		return Cast<ATank>(PlayerPawn);
}

