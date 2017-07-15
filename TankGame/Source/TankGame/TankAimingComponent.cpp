// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"

//IWYU
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
//IWYU



// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel || !Turret) {return; }

	FVector TossVelocity;
	FVector StartLocation = Barrel->GetSocketLocation("LaunchPoint");
	
	bool canItHit = UGameplayStatics::SuggestProjectileVelocity(this, TossVelocity, StartLocation, HitLocation, LaunchSpeed, false, 0.f, 0.f, ESuggestProjVelocityTraceOption::DoNotTrace);

	if ( canItHit )
	{
		FVector AimDirection = TossVelocity.GetSafeNormal();

		//UE_LOG(LogTemp, Warning, TEXT("@%f: %s : Aim solution found"), GetWorld()->GetTimeSeconds(), *GetOwner()->GetName())
		MoveBarrel(AimDirection);

	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("@%f: %s Aim solution NOT found"), GetWorld()->GetTimeSeconds(), *GetOwner()->GetName())
	}
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	FRotator CurrentRotation = Barrel->GetComponentRotation();
	FRotator RotationToSet = AimDirection.Rotation();
	FRotator DeltaRotator = RotationToSet - CurrentRotation;


	Barrel->Elevate(DeltaRotator.Pitch); 
	Turret->Rotate(DeltaRotator.Yaw);

	

}

void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	if (!BarrelToSet) { return; }
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret * TurretToSet)
{
	if (!TurretToSet) { return; }
	Turret = TurretToSet;
}



