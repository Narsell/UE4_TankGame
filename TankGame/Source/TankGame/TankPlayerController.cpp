// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"

//IWYU
#include "Engine/World.h"
#include "Tank.h"

//IWYU



void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (ensure(AimingComponent))
	{
		FoundAimingComponent(AimingComponent);
	}
	
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair(); 

}

void ATankPlayerController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnTankDeath);

	}

}

void ATankPlayerController::OnTankDeath()
{
	StartSpectatingOnly();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; }
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	
	if (!ensure( AimingComponent || GetPawn() )) { return; }

	FVector HitLocation; //Out param
	if (GetSightRayHitLocation(HitLocation))
	{
		AimingComponent->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const
{
	//Get the crosshair aim pixel location.

	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY); //OUT params.
	FVector2D ScreenLocation = FVector2D(ViewportSizeX*CrossHairLocationX, ViewportSizeY*CrossHairLocationY);

	//Project the crosshair into a world direction.

	FVector WorldDirection; //OUT param
	if (GetLookDirection(ScreenLocation, WorldDirection)) 
	{
		return GetLookVectorHitLocation(WorldDirection, HitLocation);
	}
		
	return false; 
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector WorldDirection, FVector &HitLocation) const
{
	FHitResult HitResult;
	FVector Start = PlayerCameraManager->GetCameraLocation();
	FVector End = Start + WorldDirection*LineTraceReach;

	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Camera)) 
	{
		HitLocation = HitResult.Location; //Setting the OUT param
		return true;
	}

	HitLocation = FVector();
	return false;
		
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector &WorldDirection) const
{
	FVector CameraLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraLocation, WorldDirection); 
	
}

