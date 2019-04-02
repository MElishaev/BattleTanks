// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	auto SlipSidewaysSpeed = FVector::DotProduct(GetRightVector(),GetComponentVelocity());

	// Zeroing the sideway slip speed
	auto SlipCorrectAcc = -SlipSidewaysSpeed / DeltaTime * GetRightVector();

	auto TankMesh = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = TankMesh->GetMass() * SlipCorrectAcc / 2;
	TankMesh->AddForce(CorrectionForce);
}


void UTankTrack::SetThrottle(float Throttle)
{
	// TODO: clamp the throttle of the tank
	auto ForceApplied = TrackMaxDrivingForce * Throttle * GetForwardVector();
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}