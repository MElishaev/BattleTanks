// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Engine/World.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController isn't possessing a tank"));
		return;
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("The ControlledTank is %s"), *ControlledTank->GetName());
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimAtCrosshair();
}

ATank * ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimAtCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation; // Out parameter

	if (GetSightRayHitLocation(HitLocation))
	{
		// TODO tell the controlled tank to aim at that point
		GetControlledTank()->AimAt(HitLocation);
	}
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



