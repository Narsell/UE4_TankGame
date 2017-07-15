// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKGAME_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:

	void Elevate(float RelativeSpeed);

private:

	UPROPERTY(EditAnywhere, Category = SetUp)
		float MaxDegreesPerSecond = 10.f; 
	UPROPERTY(EditAnywhere, Category = SetUp)
		float MaxElevation = 35.f;
	UPROPERTY(EditAnywhere, Category = SetUp)
		float MinElevation = 0.f;
	
	
};
