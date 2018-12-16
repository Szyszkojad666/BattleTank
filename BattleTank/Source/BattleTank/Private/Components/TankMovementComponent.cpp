// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrackComponent.h"

void UTankMovementComponent::Initialise(UTankTrackComponent* LeftTrackToSet, UTankTrackComponent* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
	if (LeftTrack && RightTrack)
	{
		LeftTrack->SetTrackDrivingForce(MaxDrivingForce);
		RightTrack->SetTrackDrivingForce(MaxDrivingForce);
	}
}

//TODO: Find a way to handle input in two directions at the same time without constantly overwriting throw values in two methods 
void UTankMovementComponent::MoveForward(float Throw)
{
	if (Throw != 0.0f)
	{
		if (ensure(LeftTrack && RightTrack))
		{
			LeftTrack->SetThrottle(Throw);
			RightTrack->SetThrottle(Throw);
		}
	}
}

void UTankMovementComponent::TurnRight(float Throw)
{
	if (Throw != 0.0f)
	{
		if (ensure(LeftTrack && RightTrack))
		{
			RightTrack->SetThrottle(-Throw);
			LeftTrack->SetThrottle(Throw);
		}
	}
}

// Called by nav component
void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	FVector NormalizedMoveVelocity = MoveVelocity.GetSafeNormal(); // Get a perpendicular vector to the direction of pathfinding goal
	FVector TankForwardVector = GetOwner()->GetActorForwardVector().GetSafeNormal(); // Get a perpendicular vector to the direction the tank is facing
	MoveForward(FVector::DotProduct(NormalizedMoveVelocity, TankForwardVector)); // Get the parallelness of these two vectors, maximum when vectors are parallel and zero when they are perpendicular
	// UE_LOG(LogTemp, Warning, TEXT("Move velocity is: %s"), *MoveVelocityString);
	TurnRight(FVector::CrossProduct(TankForwardVector, NormalizedMoveVelocity).Z); // Get the perpendicularity of these two vectors, maximum when vectors are perpendicular and zero when they are parallel
}

void UTankMovementComponent::BeginPlay()
{
	Super::BeginPlay();
}