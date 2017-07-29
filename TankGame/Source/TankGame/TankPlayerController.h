// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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

protected:

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimCompRef);


private:

	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector &HitLocation) const; //Gets world location of the point where the line trace hits the world, returns true if hits, false otherwise.

	bool GetLookDirection(FVector2D ScreenLocation, FVector &WorldDirection) const;

	bool GetLookVectorHitLocation(FVector WorldDirection, FVector &HitLocation) const;

	UPROPERTY(EditDefaultsOnly)
		float CrossHairLocationX = 0.5f;
	UPROPERTY(EditDefaultsOnly)
		float CrossHairLocationY = 0.3333f;
	UPROPERTY(EditDefaultsOnly)
		float LineTraceReach = 1000000.f;
};
