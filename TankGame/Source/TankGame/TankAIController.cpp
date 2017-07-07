// Fill out your copyright notice in the Description page of Project Settings.

//IWYU
#include "Engine/World.h"

//IWYU

#include "Tank.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();



}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!GetPlayerTank() ) 	{ return; }

	FVector HitLocation = GetPlayerTank()->GetActorLocation();
	GetControlledAITank()->AimAt(HitLocation);

}


ATank* ATankAIController::GetControlledAITank() const
{
	
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn(); // hm? 

	if (!PlayerPawn) { return nullptr; }

	else
		return Cast<ATank>(PlayerPawn);
}

