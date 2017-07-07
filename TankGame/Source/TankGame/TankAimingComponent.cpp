// Fill out your copyright notice in the Description page of Project Settings.

//IWYU
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
//IWYU

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
	
	bool canItHit = UGameplayStatics::SuggestProjectileVelocity(this, TossVelocity, StartLocation, HitLocation, LaunchSpeed, false, 0.f, 0.f, ESuggestProjVelocityTraceOption::DoNotTrace);

	if ( canItHit )
	{
		FVector AimDirection = TossVelocity.GetSafeNormal();

		UE_LOG(LogTemp, Warning, TEXT("@%f: %s calculated velocity's vector required: %s"), GetWorld()->GetTimeSeconds(), *GetOwner()->GetName(), *AimDirection.ToString())
		MoveBarrel(AimDirection);

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("@%f: %s could not calculate velocity's vector required"), GetWorld()->GetTimeSeconds(), *GetOwner()->GetName())
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



