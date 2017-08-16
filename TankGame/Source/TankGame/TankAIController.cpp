// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"



//IWYU
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"

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
	UE_LOG(LogTemp, Warning, TEXT("Tank ded lul git gud fagget"))
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn(); // hm? 
	auto AITank = GetPawn();
	auto AimingComponent = AITank->FindComponentByClass<UTankAimingComponent>();


	if (!ensure(PlayerTank || AimingComponent)) { return; }

		// Move towards the player
		MoveToActor(PlayerTank, AcceptanceRadius); //TODO check AcceptanceRadius value.

		//Aim towards the player
		AimingComponent->AimAt(PlayerTank->GetActorLocation());

		if (AimingComponent->GetFiringState() == EFiringStatus::Locked)
			AimingComponent->Fire(); //TODO: Fire  only when locked
	
	
}

