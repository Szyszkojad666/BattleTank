// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank_AIController.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Engine/World.h"




void ABattleTank_AIController::BeginPlay()
{
	Super::BeginPlay();
	ControlledTank = Cast<ATank>(GetPawn());
	GetPlayerTank();
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
}

void ABattleTank_AIController::AimTowardsCrosshair()
{
	if (ControlledTank && PlayerTank)
	{
		FVector AimLocation = PlayerTank->GetActorLocation();
		ControlledTank->AimAt(AimLocation);
	}
}


