// Copyright Nameless Studio

#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::Initialize(UTankTrack* RightTrackToSet, UTankTrack* LeftTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Scale)
{
	if (!ensure(RightTrack || LeftTrack))
	{
		UE_LOG(LogTemp, Warning, TEXT("could not find track to set"));
		return;
	}
	LeftTrack->SetThrottle(Scale);
	RightTrack->SetThrottle(Scale);
}

void UTankMovementComponent::IntendTurnRight(float Scale)
{
	if (!ensure(RightTrack || LeftTrack))
	{
		UE_LOG(LogTemp, Warning, TEXT("could not find track to set"));
		return;
	}
	LeftTrack->SetThrottle(Scale);
	RightTrack->SetThrottle(-Scale);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto TankFacingVector = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIMovementIntention = MoveVelocity.GetSafeNormal();
	
	auto ForwardMovementScale = FVector::DotProduct(TankFacingVector, AIMovementIntention);
	IntendMoveForward(ForwardMovementScale);

	auto RightMovementScale = FVector::CrossProduct(TankFacingVector, AIMovementIntention).Z;
	IntendTurnRight(RightMovementScale);
}

