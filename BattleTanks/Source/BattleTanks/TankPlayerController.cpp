// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"

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
		UE_LOG(LogTemp, Warning, TEXT("The crosshair hitting: %s"), *HitLocation.ToString());
		// TODO tell the controlled tank to aim at that point
}

// get world location where the linetrace intersects the landscape, TRUE if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitResult) const
{
	// Getting screen size - why?
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	// Pixel coordinates of the crosshair
	FVector2D ScreenLocation = FVector2D(ViewportSizeX*CrosshairXLocation, ViewportSizeY*CrosshairYLocation);
	
	return false;



	//FHitResult Hit;
	//// Get View point of the player each frame 
	//FRotator PlayerViewPointRotation;
	//FVector PlayerViewPointVector;
	//GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointVector, PlayerViewPointRotation);
	//UE_LOG(LogTemp, Warning, TEXT("PlayerViewPointRotation: %s	PlayerViewPointVector: %s"), *PlayerViewPointRotation.ToString(), *PlayerViewPointVector.ToString());

	//// Linetrace from player view for later use on objects in reach
	//FVector End = PlayerViewPointVector + PlayerViewPointRotation.Vector() * 10000.f;

	//FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	//GetWorld()->LineTraceSingleByObjectType(
	//	Hit,
	//	PlayerViewPointVector,
	//	End,
	//	FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldStatic),
	//	TraceParameters
	//);
	//// get the first landscape coordinates it hits
	//OutHitResult = Hit.Location;
	//UE_LOG(LogTemp, Warning, TEXT("HitResult is: %s"), *OutHitResult.ToString());

	//return OutHitResult.IsZero();
}



