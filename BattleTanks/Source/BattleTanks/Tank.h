// Copyright Nameless Studio

#pragma once

#include "CoreMinimal.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

public:	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
