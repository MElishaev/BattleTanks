// Copyright Nameless Studio

#include "Tank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankMovementComponent.h"
#include "TankAimingComponent.h"

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	UE_LOG(LogTemp, Warning, TEXT("NAMNAM: %s constructed"), *GetName());
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("NAMNAM: %s Begin play"), *GetName());
}

void ATank::AimAt(FVector HitLocation)
{
	if (!TankAimingComponent) { return; }
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire()
{
	bool isReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTimeInSeconds;
	
	if (Barrel && isReloaded)
	{
		// Spawn projectile at the socket of the barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
															  Barrel->GetSocketLocation(FName("Projectile")),
															  Barrel->GetSocketRotation(FName("Projectile")));
		Projectile->Launch(LaunchSpeed);

		LastFireTime = GetWorld()->GetTimeSeconds();
	}
}

