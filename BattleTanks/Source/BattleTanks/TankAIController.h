// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	// How close the AI tank wants to get to the player in cm
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float AcceptanceRadius = 10000;
private:
	void BeginPlay() override;

	virtual void SetPawn(APawn* InPawn) override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnTankDeath();
};
