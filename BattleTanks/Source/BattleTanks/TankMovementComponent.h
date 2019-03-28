// Copyright Nameless Studio

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

	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendMoveForward(float Scale);

	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendTurnRight(float Scale);

private:
	// Pathfinding logic of AI tanks
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxTankSpeed = 20000; // cm/s
};