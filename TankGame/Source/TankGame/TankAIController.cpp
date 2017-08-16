// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"



//IWYU
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
#include "GameFramework/Actor.h"

//IWYU


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();



}

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
	
	}

}

void ATankAIController::OnTankDeath()
{
	if (!ensure(GetPawn())) { return; }
	GetPawn()->DetachFromControllerPendingDestroy();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto AITank = GetPawn();
	auto AimingComponent = AITank->FindComponentByClass<UTankAimingComponent>();


	if (!(PlayerTank && AimingComponent)) { return; } //its ok if this is true, no need to ensure.

		// Move towards the player
		MoveToActor(PlayerTank, AcceptanceRadius); 

		//Aim towards the player
		AimingComponent->AimAt(PlayerTank->GetActorLocation());

		if (AimingComponent->GetFiringState() == EFiringStatus::Locked)
			AimingComponent->Fire(); 
	
	
}

