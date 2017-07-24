// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"


//IWYU
#include "Engine/World.h"

//IWYU


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();



}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn(); // hm? 
	auto AITank = Cast<ATank>(GetPawn());

	if (PlayerTank) 
	{

		//TODO Move towards the player

		//Aim towards the player
		AITank->AimAt(PlayerTank->GetActorLocation());


		AITank->Fire(); //TODO Limit fire rate
	}


}

