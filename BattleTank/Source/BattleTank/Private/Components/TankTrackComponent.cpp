// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrackComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"

UTankTrackComponent::UTankTrackComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	this->OnComponentHit.AddDynamic(this, &UTankTrackComponent::OnCompHit);
	SetNotifyRigidBodyCollision(true);
}


float UTankTrackComponent::CalculateSlippageSpeed()
{
	auto SideVelocity = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	return SideVelocity;
}

FVector UTankTrackComponent::CalculateCorrection()
{
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto Correction = -CalculateSlippageSpeed() / DeltaTime * GetRightVector();
	return Correction;
}

void UTankTrackComponent::ApplySideMovementCorrection()
{
	if (!ensure(OwnerRoot)) { return; }
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectionForce = OwnerRoot->GetMass() * CalculateCorrection() / 2;
	OwnerRoot->AddForce(CorrectionForce);
}

void UTankTrackComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
}

void UTankTrackComponent::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankTrackComponent::DriveTrack()
{
	FVector Force = GetForwardVector() * CurrentThrottle * TankMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	if (OwnerRoot)
	OwnerRoot->AddForceAtLocation(Force, ForceLocation);
	FString TrackName = GetName();
	//UE_LOG(LogTemp, Warning, TEXT("%s's current throttle is: %f: "), *TrackName, CurrentThrottle);
}

void UTankTrackComponent::OnCompHit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	DriveTrack();
	ApplySideMovementCorrection();
	CurrentThrottle = 0;
}