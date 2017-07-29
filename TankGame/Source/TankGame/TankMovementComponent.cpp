// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"
void UTankMovementComponent::Initialize(UTankTrack * LeftTrackToSet, UTankTrack * RightTrackToSet)
{
	

	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	

		LeftTrack->SetThrottle(Throw);
		RightTrack->SetThrottle(Throw);
	
}


void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	
		LeftTrack->SetThrottle(Throw);
		RightTrack->SetThrottle(-Throw);
	

}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	FVector AIMovementIntention = MoveVelocity.GetSafeNormal();
	FVector TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();

	float ThrowForward = FVector::DotProduct(AIMovementIntention, TankForward);
	float ThrowTurnRight = FVector::CrossProduct(TankForward, AIMovementIntention).Z;

	IntendMoveForward(ThrowForward);
	IntendTurnRight(ThrowTurnRight);

}


