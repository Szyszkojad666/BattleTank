// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrelComponent.h"
#include "Engine/World.h"


void UTankBarrelComponent::Elevate(float RelativeSpeed, float MaxElevationSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	auto ElevationChange = RelativeSpeed * MaxElevationSpeed * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = FMath::Clamp(RelativeRotation.Pitch + ElevationChange, MinElevationDegrees, MaxElevationDegrees);
	SetRelativeRotation(FRotator(RawNewElevation, 0, 0));
}
