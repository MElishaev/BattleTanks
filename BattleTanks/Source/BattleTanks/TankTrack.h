// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Implements the application of forces on the tank.
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class BATTLETANKS_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);
	
	// Force on track per newton
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 20000000;

private:
	UTankTrack();

	virtual void BeginPlay() override;

	TArray<class ASprungWheel*> GetWheels() const;
	
	void DriveTarck(float CurrentThrottle);
};
