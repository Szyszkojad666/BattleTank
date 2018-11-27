// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrackComponent.h"

void UTankMovementComponent::Initialise(UTankTrackComponent* LeftTrackToSet, UTankTrackComponent* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::MoveForward(float Throw, float Speed)
{
	if (LeftTrack && RightTrack)
	{
		//UE_LOG(LogTemp, Warning, TEXT("It's working: %f"), Throw);
		LeftTrack->SetThrottle(Throw, Speed);
		RightTrack->SetThrottle(Throw, Speed);
	}
}

void UTankMovementComponent::TurnRight(float Throw, float Speed)
{
	if (LeftTrack && RightTrack)
	{
		if (Throw > 0.0)
		{
			RightTrack->SetThrottle(-Throw, Speed);
			LeftTrack->SetThrottle(Throw, Speed);
		}
		if (Throw < 0.0)
		{
			RightTrack->SetThrottle(-Throw, Speed);
			LeftTrack->SetThrottle(Throw, Speed);
		}
	}
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	FString MoveVelocityString = MoveVelocity.ToString();
	UE_LOG(LogTemp, Warning, TEXT("Move velocity is: %s"), *MoveVelocityString);
}
