// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTank_PlayerController.h"
#include "Tank.h"
#include "../Public/BattleTank_PlayerController.h"

void ABattleTank_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	ControlledTank = Cast<ATank>(GetPawn());
}
