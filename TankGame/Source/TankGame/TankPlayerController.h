// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TANKGAME_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public: 

	void BeginPlay() override;
	void Tick(float DeltaTime) override;

private:

	ATank* GetControlledTank() const;
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector &HitLocation) const; //Gets world location of the point where the line trace hits the world, returns true if hits, false otherwise.
	bool GetLookDirection(FVector2D ScreenLocation, FVector &WorldDirection) const;
	bool GetLookVectorHitLocation(FVector WorldDirection, FVector &HitLocation) const;

	UPROPERTY(EditAnywhere)
		float CrossHairLocationX = 0.5f;
	UPROPERTY(EditAnywhere)
		float CrossHairLocationY = 0.3333f;
	UPROPERTY(EditAnywhere)
		float LineTraceReach = 1000000.f;
};
