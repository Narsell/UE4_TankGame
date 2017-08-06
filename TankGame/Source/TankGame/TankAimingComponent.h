// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringStatus : uint8 

{
	Reloading, 
	Aiming, 
	Locked,
	OutOfAmmo


};


class UTankTurret;
class UTankBarrel;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKGAME_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();


protected:
	// Called when the game starts
	virtual void BeginPlay() override; 
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus FiringState = EFiringStatus::Aiming;

public:	

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);
	UFUNCTION(BlueprintCallable, Category = "Input")
	void Fire();
	UFUNCTION(BlueprintCallable, Category = "Firing")
	int32 GetAmmo() const;

	EFiringStatus GetFiringState() const;
	void AimAt(FVector HitLocation);

private:

	void MoveBarrel(FVector AimDirection);
	bool IsBarrelMoving();

	FVector AimDirection;
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 5000.f; //Real values go from 40,000 cm/s to 100,000 cm/s, But that's not fun

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeSeconds = 3.f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint; //Telling the editor to list only childs of the class AProjectile.

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int32 Ammo = 3;

	double LastFireTime = 0;




	
};
