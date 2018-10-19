// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank_AIController.h"
#include "Classes/Kismet/GameplayStatics.h"

#include "Tank.h"
#include "Engine/World.h"






ATank* ABattleTank_AIController:: GetPlayerTank()
{
	ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
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
}

void ABattleTank_AIController::AimTowardsCrosshair()
{
}


