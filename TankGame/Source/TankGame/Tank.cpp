// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankMovementComponent.h"


//IWYU
#include "Engine/World.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	UE_LOG(LogTemp, Warning, TEXT("NORMIE: %s Tank c++ constructed"), *GetName())

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("NORMIE: %s Tank c++ Begin Play"), *GetName())

}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ATank::Fire()
{
	if (!ensure(Barrel) ) { return; }
	
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeSeconds;
	static bool isBeginPlay = true;

	if (isReloaded || isBeginPlay) 
	{
		
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation("LaunchPoint"), Barrel->GetSocketRotation("LaunchPoint"));
		Projectile->LaunchProjectile(LaunchSpeed);

		LastFireTime = FPlatformTime::Seconds();
		isBeginPlay = false;
	
	}


}

void ATank::AimAt(FVector HitLocation)
{
	if ( !ensure(TankAimingComponent) ) { return; }
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
	
}



