// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "TankAimingComponent.h"


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

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }

	FVector TossVelocity;
	FVector StartLocation = Barrel->GetSocketLocation("LaunchPoint");
	
	if ( UGameplayStatics::SuggestProjectileVelocity(this, TossVelocity, StartLocation, HitLocation, LaunchSpeed, false, 0.f, 0.f, ESuggestProjVelocityTraceOption::DoNotTrace) )
	{
		FVector AimDirection = TossVelocity.GetSafeNormal();
		UE_LOG(LogTemp, Warning, TEXT("%s pointing at: %s"), *GetOwner()->GetName(), *AimDirection.ToString())
		MoveBarrel(AimDirection);

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s failed to suggest projectile velocity"), *GetOwner()->GetName())
	}
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	FRotator CurrentRotation = Barrel->GetComponentRotation();
	FRotator RotationToSet = AimDirection.Rotation();
	auto DeltaRotator = RotationToSet - CurrentRotation;

	Barrel->Elevate(5); //TODO pass an actual value

	

}

void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	Barrel = BarrelToSet;
}



