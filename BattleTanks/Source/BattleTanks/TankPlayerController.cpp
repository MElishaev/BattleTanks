// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Camera/PlayerCameraManager.h"
#include "Tank.h"
#include "Engine/World.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	FoundTankAimingComponent(AimingComponent);
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimAtCrosshair();
}

void ATankPlayerController::AimAtCrosshair()
{
	if (!GetPawn()) { return; }
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	FVector HitLocation; // Out parameter

	if (GetSightRayHitLocation(HitLocation))
	{
		AimingComponent->AimAt(HitLocation);
	}
}

void ATankPlayerController::OnTankDeath()
{
	StartSpectatingOnly();
}

// get world location where the linetrace intersects the landscape, TRUE if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitResult) const
{
	// Getting screen size of the game
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	// Pixel coordinates of the crosshair
	FVector2D ScreenLocation = FVector2D(ViewportSizeX*CrosshairXLocation, ViewportSizeY*CrosshairYLocation);
	//Convert 2D screen position to World Space 3D position and direction. Returns false if unable to determine value.
	FVector WordLocation, LookDirection;
	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WordLocation, LookDirection))
	{
		// Line trace along the look direction to see what it hits
		return GetLookVectorHitLocation(LookDirection, OutHitResult);
	}
	return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitResult) const
{
	FHitResult HitResult;
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		PlayerCameraManager->GetCameraLocation(),
		PlayerCameraManager->GetCameraLocation() + LookDirection*LineTraceRange,
		ECollisionChannel(ECC_Visibility)
		))
	{
		OutHitResult = HitResult.ImpactPoint;
		return true;
	}
	else return false;
}

void ATankPlayerController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);

	ATank* PossessedTank = Cast<ATank>(InPawn);
	if (!ensure(PossessedTank)) { return; }

	PossessedTank->OnTankDeath.AddUniqueDynamic(this, &ATankPlayerController::OnTankDeath);
}



