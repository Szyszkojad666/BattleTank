// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank_AIController.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Engine/World.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "TankMovementComponent.h"
#include "TankAimingComponent.h"
#include "Classes/GameFramework/Pawn.h"

void ABattleTank_AIController::BeginPlay()
{
	Super::BeginPlay();
	ControlledPawn = GetPawn();
	GetPlayerTank();
	FTimerHandle TimerHandle;
	// GetWorldTimerManager().SetTimer(TimerHandle, this, &ABattleTank_AIController::Fire, 2.0f, true, 3.0f);
	if (ControlledPawn)
	{
		TankMovementComp = Cast<UTankMovementComponent>(ControlledPawn->GetComponentByClass(UTankMovementComponent::StaticClass()));
		TankAimingComp = Cast<UTankAimingComponent>(ControlledPawn->GetComponentByClass(UTankAimingComponent::StaticClass()));
	}
}

void ABattleTank_AIController::Fire()
{
	if (ControlledPawn && TankAimingComp)
	{
		TankAimingComp->Fire();
	}
}

ATank* ABattleTank_AIController:: GetPlayerTank()
{
	PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (!PlayerTank)
	{
		return nullptr;
	}
	else
		return PlayerTank;
}

void ABattleTank_AIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABattleTank_AIController::AimTowardsCrosshair()
{
	if (TankAimingComp && PlayerTank)
	{
		FVector AimLocation = PlayerTank->GetActorLocation();
		TankAimingComp->AimAt(AimLocation);
	}
}

FPathFollowingRequestResult ABattleTank_AIController::MoveTo(const FAIMoveRequest & MoveRequest, FNavPathSharedPtr * OutPath)
{
	Super::MoveTo(MoveRequest, OutPath);
	FVector Destination = MoveRequest.GetDestination();
	FVector Velocity = Destination - ControlledPawn->GetActorLocation();
	if (TankMovementComp)
	{
		TankMovementComp->RequestDirectMove(Velocity, false);
	}
	return FPathFollowingRequestResult();
}

void ABattleTank_AIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		ATank* PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }
		PossessedTank->OnTankDeath.AddUniqueDynamic(this, &ABattleTank_AIController::OnPawnDeath);
	}
}

void ABattleTank_AIController::OnPawnDeath()
{
	ControlledPawn->SetLifeSpan(0.1f);
}