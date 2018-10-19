// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTank_PlayerController.h"
#include "Tank.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "../Public/BattleTank_PlayerController.h"
#include "Classes/Camera/CameraComponent.h"
#include "Classes/GameFramework/SpringArmComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "BattleTank.h"

static int32 DebugAimingDrawing = 0;
FAutoConsoleVariableRef CVARDebugAimingDrawing(
	TEXT("d.DebugAiming"),
	DebugAimingDrawing,
	TEXT("Draw debug traces for aiming"),
	ECVF_Cheat);

ABattleTank_PlayerController::ABattleTank_PlayerController()
{
	AimRange = 10000.0f;
	CrosshairXLocation = 0.5;
	CrosshairYLocation = 0.33333;
}

void ABattleTank_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	ControlledTank = Cast<ATank>(GetPawn());
}

void ABattleTank_PlayerController::Tick(float DeltaTime)
{
	AimTowardsCrosshair();
}

void ABattleTank_PlayerController::AimTowardsCrosshair()
{
	if (!ControlledTank) { return; }
	FHitResult HitResult;
	if (GetAimLocation(HitResult))
	{
		UE_LOG(LogTemp, Warning, TEXT("HitLocation is: %s"), *HitResult.Location.ToString());
	}
}

bool ABattleTank_PlayerController::GetAimLocation(FHitResult& Hit) const
{
	//Query params
	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.AddIgnoredActor(ControlledTank);
	QueryParams.bTraceComplex = true;
	QueryParams.bReturnPhysicalMaterial = true;

	//Trace variables declaration
	FVector CameraLocation;
	FRotator ShotDirection;
	FVector TraceEnd;
	FVector TracerEnd;

	//Set Viewport Size Variables
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	if (ControlledTank)
	{
		GetPlayerViewPoint(CameraLocation, ShotDirection);
		ShotDirection.Pitch += AimPitchOffset;
		TraceEnd = CameraLocation + (ShotDirection.Vector() * AimRange);
		TracerEnd = TraceEnd;
		if (DebugAimingDrawing > 0)
		{
			DrawDebugLine(GetWorld(), CameraLocation, TraceEnd, FColor::Red, false, 1.0f, 0, 1.0f);
		}
		if (GetWorld()->LineTraceSingleByChannel(HitResult, CameraLocation, TraceEnd, COLLISION_WEAPON, QueryParams))
		{
			if (DebugAimingDrawing > 0)
			{
				DrawDebugSphere(GetWorld(), HitResult.Location, 100.0f, 12, FColor::Red, false, 0.5f, 0, 3.0f);
			}
			Hit = HitResult;
			return true;
		}
	}
	return false;
}

void ABattleTank_PlayerController::GetPlayerViewPoint(FVector & Location, FRotator & Rotation) const
{
	Super::GetPlayerViewPoint(Location, Rotation);
}
