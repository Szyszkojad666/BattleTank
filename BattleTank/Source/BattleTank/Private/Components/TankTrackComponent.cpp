// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrackComponent.h"

UTankTrackComponent::UTankTrackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	ApplyCorrection(DeltaTime);
}

float UTankTrackComponent::CalculateSlippageSpeed()
{
	auto SideVelocity = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	UE_LOG(LogTemp, Warning, TEXT("Tank's sideways velocity is: %f "), SideVelocity);
	return SideVelocity;
}

FVector UTankTrackComponent::CalculateCorrection(float DeltaTime)
{
	auto Correction = -CalculateSlippageSpeed() / DeltaTime * GetRightVector();
	return Correction;
}

void UTankTrackComponent::ApplyCorrection(float DeltaTime)
{
	if (!ensure(OwnerRoot)) { return; }
	auto CorrectionForce = OwnerRoot->GetMass() * CalculateCorrection(DeltaTime) / 2;
	OwnerRoot->AddForce(CorrectionForce);
}

void UTankTrackComponent::BeginPlay()
{
	OwnerRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
}

void UTankTrackComponent::SetThrottle(float Throttle, float MaxForce)
{
	FVector Force = GetForwardVector() * Throttle * MaxForce;
	FVector ForceLocation = GetComponentLocation();
	auto TankRoot =Cast<UPrimitiveComponent>( GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(Force, ForceLocation);
}


