// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"


//IWYU
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile Movement Component");
	ProjectileMovementComponent->bAutoActivate = false;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>("Collision Mesh");
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	//CollisionMesh->SetVisibility(false); TODO: uncomment when finished debugging.

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>("LaunchBlast");
	LaunchBlast->AttachTo(RootComponent); //It attaches itself to the collision mesh but better be sure :)

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProjectile::LaunchProjectile(float Speed)
{
	ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMovementComponent->Activate();
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

