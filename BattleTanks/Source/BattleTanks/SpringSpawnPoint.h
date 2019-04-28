// Copyright Nameless Studio

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SpringSpawnPoint.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API USpringSpawnPoint : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpringSpawnPoint();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	AActor* GetSpawnedActor() const;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;


private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TSubclassOf<AActor> SpawnClass;
		
	UPROPERTY()
		AActor* SpawnedActor = nullptr;
};
