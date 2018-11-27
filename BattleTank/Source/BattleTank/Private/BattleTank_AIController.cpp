// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank_AIController.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Engine/World.h"
#include "Runtime/Engine/Public/TimerManager.h"



void ABattleTank_AIController::BeginPlay()
{
	Super::BeginPlay();
	ControlledTank = Cast<ATank>(GetPawn());
	GetPlayerTank();
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ABattleTank_AIController::Fire, 2.0f, true, 3.0f);
}

void ABattleTank_AIController::Fire()
{
	if (ControlledTank)
	{
		ControlledTank->Fire();
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
	AimTowardsCrosshair();
	if (PlayerTank)
	{
		MoveToActor(PlayerTank, 300.0f);
	}
	
}

void ABattleTank_AIController::AimTowardsCrosshair()
{
	if (ControlledTank && PlayerTank)
	{
		FVector AimLocation = PlayerTank->GetActorLocation();
		ControlledTank->AimAt(AimLocation);
	}
}


