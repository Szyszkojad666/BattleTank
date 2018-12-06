// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Classes/Components/StaticMeshComponent.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "Tank.h"
#include "TankBarrelComponent.h"
#include "TankTurretComponent.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	MyOwnerTank = Cast<ATank>(GetOwner());
}

void UTankAimingComponent::Initialize(UTankBarrelComponent * BarrelRef, UTankTurretComponent * TurretRef)
{
	if (BarrelRef && TurretRef)
	{
		Barrel = BarrelRef;
		Turret = TurretRef;
	}	
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector Location, float LaunchSpeed)
{
	if (!Barrel) { return; }
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation("S_Muzzle");
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetOwner());
	bool HaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		Location,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (HaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrel(AimDirection);
	}
	else
	{
		FRotator AimRotaton = UKismetMathLibrary::FindLookAtRotation(GetOwner()->GetActorLocation(), Location);
		FVector AimDirection = AimRotaton.Vector();
		MoveBarrel(AimDirection);
	}
	
}

void UTankAimingComponent::MoveBarrel(FVector ShotDirection)
{
	if (MyOwnerTank)
	{
		FRotator ShotDirectionRot = ShotDirection.Rotation();
		FRotator BarrelRot = Barrel->GetForwardVector().Rotation();
		FRotator DeltaRotator = ShotDirectionRot - BarrelRot;
		MyOwnerTank->AimBarrel.Broadcast(DeltaRotator);
		if (Barrel && Turret)
		{
			Barrel->Elevate(DeltaRotator.Pitch);
			Turret->Rotate(DeltaRotator.Yaw);
		}
	}
}

