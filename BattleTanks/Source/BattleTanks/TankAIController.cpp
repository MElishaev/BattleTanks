// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto AIControlledTank = GetAIControlledTank();
	if (!AIControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIControlledTank isn't possessing a tank"));
		return;
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("The AI-ControlledTank is %s"), *AIControlledTank->GetName());
}

ATank * ATankAIController::GetAIControlledTank()
{
	return Cast<ATank>(GetPawn());
}
