// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"


UCLASS()
class TANKGAME_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	//Returns current health as a percentage of starting health.
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override; 

private:

	UPROPERTY(EditDefaultsOnly, Category = "Attributes")
	int32 StartingHealth = 100.f;

	UPROPERTY(VisibleAnywhere, Category = "Attributes")
	int32 CurrentHealth = StartingHealth;




	
	
};
