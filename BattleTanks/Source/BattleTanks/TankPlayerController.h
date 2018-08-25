// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankAimingComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	ATank * GetControlledTank() const;
	
	// Aim the barrel to the point where the linetrace of the crosshair hits the landscape
	void AimAtCrosshair();

private:
	// Crosshair location
	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5;

	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.333333;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.f;

	// Get the Point where the linetrace hit the landscape
	bool GetSightRayHitLocation(FVector&) const;

	bool GetLookVectorHitLocation(FVector,FVector&) const;
};
