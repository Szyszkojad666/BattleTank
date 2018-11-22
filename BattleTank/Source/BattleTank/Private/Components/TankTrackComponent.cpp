// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrackComponent.h"



void UTankTrackComponent::SetThrottle(float Throttle, float MaxForce)
{
	FVector Force = GetForwardVector() * Throttle * MaxForce;
	FVector ForceLocation = GetComponentLocation();
	auto TankRoot =Cast<UPrimitiveComponent>( GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(Force, ForceLocation);
}
