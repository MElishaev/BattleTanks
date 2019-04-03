// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	// Registering delegate OnComponentHit
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	NegateSlipForce();
	DriveTarck();
	CurrentThrottle = 0;
}

void UTankTrack::NegateSlipForce()
{
	auto SlipSidewaysSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	// Zeroing the sideway slip speed
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	auto SlipCorrectAcc = -SlipSidewaysSpeed / DeltaTime * GetRightVector();

	auto TankMesh = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = TankMesh->GetMass() * SlipCorrectAcc / 2;
	TankMesh->AddForce(CorrectionForce);
}

void UTankTrack::DriveTarck()
{
	auto ForceApplied = TrackMaxDrivingForce * CurrentThrottle * GetForwardVector();
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTrack::SetThrottle(float Throttle)
{
	// TODO: clamp the throttle of the tank
	CurrentThrottle = CurrentThrottle + FMath::Clamp<float>(Throttle, -1, +1);
}