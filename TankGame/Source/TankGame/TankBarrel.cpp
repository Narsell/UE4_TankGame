// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

//IWYU
#include "Engine/World.h"
//IWYU



void UTankBarrel::Elevate(float RelativeSpeed)
{
	
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);

	float ElevationChange = MaxDegreesPerSecond * RelativeSpeed * GetWorld()->DeltaTimeSeconds;
	float RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	float Elevation = FMath::Clamp<float>(RawNewElevation, MinElevation, MaxElevation);


	SetRelativeRotation(FRotator(Elevation, 0, 0));
	
}
