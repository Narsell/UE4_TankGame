// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * Responsible for driving the tank tracks
 */
UCLASS(Classgroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKGAME_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
	
public:

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialize(UTankTrack * LeftTrackToSet, UTankTrack * RightTrackToSet);

	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendTurnRight(float Throw);

	void RequestDirectMove (const FVector & MoveVelocity, bool bForceMaxSpeed) override;

private:

	UTankTrack * LeftTrack = nullptr;
	UTankTrack * RightTrack = nullptr;
	
};
