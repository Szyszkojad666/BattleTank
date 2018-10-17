// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTank_PlayerController.h"
#include "Tank.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "../Public/BattleTank_PlayerController.h"
#include "Classes/Camera/CameraComponent.h"
#include "Classes/GameFramework/SpringArmComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"

static int32 DebugAimingDrawing = 0;
FAutoConsoleVariableRef CVARDebugAimingDrawing(
	TEXT("d.DebugAiming"),
	DebugAimingDrawing,
	TEXT("Draw debug traces for aiming"),
	ECVF_Cheat);

ABattleTank_PlayerController::ABattleTank_PlayerController()
{
	AimRange = 10000.0f;
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
	GetAimLocation();
}

FHitResult ABattleTank_PlayerController::GetAimLocation() const
{
	//Query params
	FHitResult Hit;
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

	if (ControlledTank)
	{
		ShotDirection = ControlledTank->Camera->GetComponentRotation();
		CameraLocation = ControlledTank->Camera->GetComponentLocation();
		TraceEnd = ControlledTank->Camera->GetComponentLocation() + (ShotDirection.Vector() * AimRange);
		TracerEnd = TraceEnd;
		if (DebugAimingDrawing > 0)
		{
			DrawDebugLine(GetWorld(), CameraLocation, Hit.TraceEnd, FColor::Red, false, 1.0f, 0, 1.0f);
		}
		if (GetWorld()->LineTraceSingleByChannel(Hit, CameraLocation, TraceEnd, ECC_Visibility, QueryParams))
		{
			return Hit;
		}
	}
	return Hit;
}