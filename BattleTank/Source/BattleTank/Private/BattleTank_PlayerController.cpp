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
#include "TankAimingComponent.h"
#include "HealthComponent.h"

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
	if (ensure(ControlledTank))
	{
		TankAimingComponent = ControlledTank->GetTankAimingComponent();
	}
}

void ABattleTank_PlayerController::Tick(float DeltaTime)
{
	AimTowardsCrosshair();
}

void ABattleTank_PlayerController::AimTowardsCrosshair()
{
	if (!ControlledTank) { return; }
	{
		GetAimLocation();
	}
}

void ABattleTank_PlayerController::GetAimLocation()
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
	FVector ShotDirection;
	FVector TraceEnd;
	FVector TracerEnd;

	//Set Viewport Size Variables
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	
	// HACK Because the crosshair position is not in the center and can be changed in the Widget
	//TODO: Read the screen position of the crosshair from the Widget  
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	
	// To find the beginning and direction of the trace
	DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraLocation, ShotDirection);

	if (ControlledTank && TankAimingComponent)
	{
		TraceEnd = CameraLocation + (ShotDirection * AimRange);
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
			TankAimingComponent->AimAt(HitResult.Location);
		}
		else
		{
			TankAimingComponent->AimAt(TraceEnd);
		}		
	}
}

void ABattleTank_PlayerController::Fire()
{
	if (!ensure(TankAimingComponent)) { return; }
	TankAimingComponent->Fire();
}

void ABattleTank_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("Fire", IE_Pressed, this, &ABattleTank_PlayerController::Fire);
}
	
void ABattleTank_PlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }
		PossessedTank->GetHealthComponent()->OnDeath.AddUniqueDynamic(this, &ABattleTank_PlayerController::OnPawnDeath);
		OnPossessed.AddUniqueDynamic(this, &ABattleTank_PlayerController::K2_OnPossessed);
		OnPossessed.Broadcast();
	}
}

void ABattleTank_PlayerController::OnPawnDeath()
{
	StartSpectatingOnly();
}