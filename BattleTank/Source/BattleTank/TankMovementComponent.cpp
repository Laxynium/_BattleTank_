// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankMovementComponent.h"
#include "TankTrack.h"
void UTankMovementComponent::Initialize(UTankTrack * LeftTrackToSet, UTankTrack * RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet)
		return;
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}
void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack)return;
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

}
void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack)return;
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);

}

void UTankMovementComponent::IntendTurnLeft(float Throw)
{
	/*if (!LeftTrack || !RightTrack)return;
	LeftTrack->SetThrottle(-Throw);
	RightTrack->SetThrottle(Throw);*/
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	//No need to call Super as we're replacing the functionality
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	auto ForwardThrow=FVector::DotProduct(TankForward, AIForwardIntention);
	auto RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	IntendMoveForward(ForwardThrow);
	IntendTurnRight(RightThrow);
}
