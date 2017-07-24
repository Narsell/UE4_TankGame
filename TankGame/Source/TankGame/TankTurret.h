// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKGAME_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

	public: 

		void Rotate(float RelativeSpeed); //TODO figure out a way to deal with rotation reset after 180°

	private:

		UPROPERTY(EditDefaultsOnly, Category = SetUp)
		float MaxDegreesPerSecond = 20.f;




	
};
