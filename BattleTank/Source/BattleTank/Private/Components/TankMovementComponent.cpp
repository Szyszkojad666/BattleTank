// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrackComponent.h"
#include "Tank.h"

void UTankMovementComponent::Initialise(UTankTrackComponent* LeftTrackToSet, UTankTrackComponent* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::MoveForward(float Throw)
{
	if (LeftTrack && RightTrack && OwnerTank)
	{
		//UE_LOG(LogTemp, Warning, TEXT("It's working: %f"), Throw);
		LeftTrack->SetThrottle(Throw, OwnerTank->TrackMaxDrivingForce);
		RightTrack->SetThrottle(Throw, OwnerTank->TrackMaxDrivingForce);
	}
}

void UTankMovementComponent::TurnRight(float Throw)
{
	if (LeftTrack && RightTrack && OwnerTank)
	{
		if (Throw > 0.0)
		{
			RightTrack->SetThrottle(-Throw, OwnerTank->TrackMaxDrivingForce);
			LeftTrack->SetThrottle(Throw, OwnerTank->TrackMaxDrivingForce);
		}
		if (Throw < 0.0)
		{
			RightTrack->SetThrottle(-Throw, OwnerTank->TrackMaxDrivingForce);
			LeftTrack->SetThrottle(Throw, OwnerTank->TrackMaxDrivingForce);
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
	OwnerTank = Cast<ATank>(GetOwner());
}