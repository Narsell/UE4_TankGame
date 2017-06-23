// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	
	if (ControlledTank)
	UE_LOG(LogTemp, Warning, TEXT("Tank Player Controller possessing: %s"), *( ControlledTank->GetName() ) )
	else 
	UE_LOG(LogTemp, Error, TEXT("Tank Player Controller not possessing a Tank actor"))
}

ATank* ATankPlayerController::GetControlledTank() const
{

	return Cast<ATank>(GetPawn());
}


