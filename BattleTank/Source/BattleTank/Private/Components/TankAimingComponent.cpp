// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Classes/Components/StaticMeshComponent.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "TankBarrelComponent.h"
#include "TankTurretComponent.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "Projectile.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Classes/Engine/World.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
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
	if (FiringState != EFiringState::Reloading)
	{
		IsAiming();
	}
}
void UTankAimingComponent::Fire()
{
	if (FiringState != EFiringState::Reloading)
	{
		if (!ensure(Barrel)) { return; }
		if (!ensure(DefaultProjectileClass)) { return; }
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(DefaultProjectileClass,
			Barrel->GetSocketLocation("S_Muzzle"),
			Barrel->GetSocketRotation("S_Muzzle"),
			SpawnParams
			);
		if (Projectile)
		{
			Projectile->Launch();
			Reload();
		}
	}
}

void UTankAimingComponent::SetReloadedAndFiringState()
{
	FiringState = EFiringState::Reloaded;
}

void UTankAimingComponent::Reload()
{
	FTimerHandle ReloadTimerHandle;
	FiringState = EFiringState::Reloading;
	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &UTankAimingComponent::SetReloadedAndFiringState, ReloadTimeInSeconds, false, ReloadTimeInSeconds);
}

void UTankAimingComponent::IsAiming()
{
	if (Barrel)
	{
		FVector Subtraction = AimDirection - Barrel->GetForwardVector();
		//UE_LOG(LogTemp, Warning, TEXT("Subtraction is %s: "), *Subtraction.ToString());
		 if (AimDirection.Equals(Barrel->GetForwardVector(), 0.01f))
		 {
			 FiringState = EFiringState::Locked;
		 }
		 else 
		 {
			 FiringState = EFiringState::Aiming;
		 }
	}	
}

void UTankAimingComponent::AimAt(FVector Location)
{
	if (!ensure(Barrel)) { return; }
	if (!ensure(DefaultProjectileClass)) { return; }
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation("S_Muzzle");
	float LaunchSpeed = DefaultProjectileClass->GetDefaultObject<AProjectile>()->LaunchSpeed;
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
		AimDirection = OutLaunchVelocity.GetSafeNormal();
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
	if (ensure(Barrel && Turret))
	{
		FRotator ShotDirectionRot = ShotDirection.Rotation();
		FRotator BarrelRot = Barrel->GetForwardVector().Rotation();
		FRotator DeltaRotator = ShotDirectionRot - BarrelRot;
		if (Barrel && Turret)
		{
			Barrel->Elevate(DeltaRotator.Pitch, BarrelElevationSpeed);
			Turret->Rotate(DeltaRotator.Yaw, TurretRotationSpeed);
		}
	}
}

