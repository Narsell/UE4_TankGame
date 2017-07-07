// Fill out your copyright notice in the Description page of Project Settings.

//IWYU
#include "Engine/World.h"

//IWYU

#include "Tank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//...............

	auto ControlledTank = GetControlledTank();
	
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair(); 

}

void ATankPlayerController::AimTowardsCrosshair()
{
	if ( !GetControlledTank() ) { return; }

	FVector HitLocation; //Out param
	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
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
		if (!GetLookVectorHitLocation(WorldDirection, HitLocation))
		{
			UE_LOG(LogTemp, Warning, TEXT("No ECC_Visibility channel objects intersected"))
			
		}
		
	}

	return true; 
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector WorldDirection, FVector &HitLocation) const
{
	FHitResult HitResult;
	FVector Start = PlayerCameraManager->GetCameraLocation();
	FVector End = Start + WorldDirection*LineTraceReach;

	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility)) 
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


ATank* ATankPlayerController::GetControlledTank() const
{

	return Cast<ATank>(GetPawn());
}


