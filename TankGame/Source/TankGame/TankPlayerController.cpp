// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//...............

	auto ControlledTank = GetControlledTank();
	
	if (ControlledTank)
	UE_LOG(LogTemp, Warning, TEXT("Tank Player Controller possessing: %s"), *( ControlledTank->GetName() ) )
	else 
	UE_LOG(LogTemp, Error, TEXT("Tank Player Controller not possessing a Tank actor"))
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair(); 

}

void ATankPlayerController::AimTowardsCrosshair()
{
	if ( !GetControlledTank() ) { return; }

	//TODO this function should make the cannon move towards the crosshair and shoot if input is received
}


ATank* ATankPlayerController::GetControlledTank() const
{

	return Cast<ATank>(GetPawn());
}


