// Copyright Nameless Studio

#pragma once

#include "CoreMinimal.h"
#include "Delegate.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	// Getting current tank's health percentage
	UFUNCTION(BlueprintPure, Category = "Tank Properties")
		float GetHealthPercent() const;

	FTankDelegate OnTankDeath;
private:	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Tank Properties")
		int32 TankHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Tank Properties")
		int32 CurrentHealth;
};
