// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrackComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "SprungWheel.h"
#include "SpawnPointComponent.h"

UTankTrackComponent::UTankTrackComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetNotifyRigidBodyCollision(true);
}

TArray<class ASprungWheel*> UTankTrackComponent::GetWheels() const
{
	TArray<ASprungWheel*> Wheels;
	TArray<USceneComponent*> Children;
	GetChildrenComponents(true, Children);
	for (USceneComponent* SceneComp : Children)
	{
		auto* SpawnerComponent = Cast<USpawnPointComponent>(SceneComp);
		if (SpawnerComponent)
		{
			AActor* SpawnedChild = SpawnerComponent->GetSpawnedActor();
			auto SprungWheel = Cast<ASprungWheel>(SpawnedChild);
			if (SprungWheel)
			{
				Wheels.Add(SprungWheel);
			}
		}
	}
	return Wheels;
}


void UTankTrackComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
}

void UTankTrackComponent::SetThrottle(float Throttle)
{
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1, 1);
	DriveTrack(CurrentThrottle);
}

void UTankTrackComponent::DriveTrack(float CurrentThrottle)
{
	auto ForceApplied = CurrentThrottle * TankMaxDrivingForce;
	auto Wheels = GetWheels();
	auto ForcePerWheel = ForceApplied / Wheels.Num();
	for (ASprungWheel * Wheel : Wheels)
	{
		Wheel->AddDrivingForce(ForcePerWheel);
	}
}
