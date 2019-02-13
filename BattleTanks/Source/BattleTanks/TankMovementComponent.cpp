// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::Initialize(UTankTrack* RightTrackToSet, UTankTrack* LeftTrackToSet)
{
	UE_LOG(LogTemp, Warning, TEXT("initialized movement component"));
	if (!RightTrackToSet || !LeftTrackToSet)
	{
		UE_LOG(LogTemp, Warning, TEXT("could not find track to set"));
		return;
	}
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Scale)
{
	UE_LOG(LogTemp, Warning, TEXT("moving %f"), Scale);
	LeftTrack->SetThrottle(Scale);
	RightTrack->SetThrottle(Scale);
}
