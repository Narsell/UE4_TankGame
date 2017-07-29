// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"


//IWYU
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

//IWYU


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();



}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn(); // hm? 
	auto AITank = GetPawn();

	if (!ensure(PlayerTank && AITank)) { return; }

		// Move towards the player
		MoveToActor(PlayerTank, AcceptanceRadius); //TODO check AcceptanceRadius value.

		//Aim towards the player
		AITank->FindComponentByClass<UTankAimingComponent>()->AimAt(PlayerTank->GetActorLocation());

		//AITank->FindComponentByClass<UTankAimingComponent>()->Fire
	
}

