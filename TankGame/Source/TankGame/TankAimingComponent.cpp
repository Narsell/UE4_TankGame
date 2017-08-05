// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

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
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeSeconds)

		FiringState = EFiringStatus::Reloading;
	else if ( IsBarrelMoving() )
		FiringState = EFiringStatus::Aiming;

	else
		FiringState = EFiringStatus::Locked;
}

bool UTankAimingComponent::IsBarrelMoving()
{


	FVector BarrelFowardVector = Barrel->GetForwardVector();
	return !BarrelFowardVector.Equals(AimDirection, 0.01f);
}


void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel || ProjectileBlueprint )) { return; }


	if (FiringState != EFiringStatus::Reloading)
	{

		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation("LaunchPoint"), Barrel->GetSocketRotation("LaunchPoint"));
		Projectile->LaunchProjectile(LaunchSpeed);

		LastFireTime = FPlatformTime::Seconds();

	}


}

EFiringStatus UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel && Turret)) { return; }
	

		FVector TossVelocity;
		FVector StartLocation = Barrel->GetSocketLocation("LaunchPoint");

		bool canItHit = UGameplayStatics::SuggestProjectileVelocity(this, TossVelocity, StartLocation, HitLocation, LaunchSpeed, false, 0.f, 0.f, ESuggestProjVelocityTraceOption::DoNotTrace);

		if (canItHit)
		{
			AimDirection = TossVelocity.GetSafeNormal();
			MoveBarrel(AimDirection);
		}
		
	

}

void UTankAimingComponent::Initialize(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	if (!ensure(Barrel || Turret)) { return; }
	

		FRotator CurrentRotation = Barrel->GetComponentRotation();
		FRotator RotationToSet = AimDirection.Rotation();
		FRotator DeltaRotator = RotationToSet - CurrentRotation;

		Barrel->Elevate(DeltaRotator.Pitch);


		if (DeltaRotator.Yaw > 180 )
			Turret->Rotate(-DeltaRotator.Yaw);
		else
			Turret->Rotate(DeltaRotator.Yaw);
}






