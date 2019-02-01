// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class BATTLETANKS_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Rotate(float RelativeSpeed);

	// TODO: changed the variable to public to check if the turret mesh still disappears
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 25;
	
};
