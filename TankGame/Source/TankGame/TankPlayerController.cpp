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

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *(HitLocation.ToString() ) )
		//TODO make controlled tank to aim at the point.
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const
{
	HitLocation = FVector(1.f); //TODO make this the actual HitLocation value.
	return true;
}


ATank* ATankPlayerController::GetControlledTank() const
{

	return Cast<ATank>(GetPawn());
}


