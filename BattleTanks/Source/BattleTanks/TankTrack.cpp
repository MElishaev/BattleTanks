// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	// TODO: clamp the throttle of the tank
	auto ForceApplied = TrackMaxDrivingForce * Throttle * GetForwardVector();
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

}