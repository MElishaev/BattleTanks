// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

#include "SprungWheel.h"
#include "SpringSpawnPoint.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
}

TArray<ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<ASprungWheel*> Wheels;

	TArray<USceneComponent*> WheelSpawnPoints;
	GetChildrenComponents(false, WheelSpawnPoints); // getting spawn points of this tank track
	for (USceneComponent* Element : WheelSpawnPoints)
	{
		auto WheelSpawnPoint = Cast<USpringSpawnPoint>(Element);
		if (!WheelSpawnPoint) continue;

		auto Wheel = Cast<ASprungWheel>(WheelSpawnPoint->GetSpawnedActor());
		if (!Wheel) continue;

		Wheels.Add(Wheel);
	}
	return Wheels;
}

void UTankTrack::DriveTarck(float CurrentThrottle)
{
	auto ForceApplied = TrackMaxDrivingForce * CurrentThrottle;
	auto Wheels = GetWheels();
	auto ForcePerWheel = ForceApplied / Wheels.Num();
	for (ASprungWheel* Wheel : Wheels)
	{
		Wheel->AddDrivingForce(ForcePerWheel);
	}
}

void UTankTrack::SetThrottle(float Throttle)
{
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1, +1);
	DriveTarck(CurrentThrottle);
}