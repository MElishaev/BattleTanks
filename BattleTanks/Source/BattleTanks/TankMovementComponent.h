// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * Tank movement class
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANKS_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialize(UTankTrack* RightTrackToSet, UTankTrack* LeftTrackToSet);

	UFUNCTION(BlueprintCallable)
	void IntendMoveForward(float Scale);

private:
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxTankSpeed = 20000; // cm/s
};
