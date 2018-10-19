// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BattleTank_AIController.generated.h"


class ATank;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ABattleTank_AIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ATank* GetPlayerTank();
	virtual void Tick(float DeltaTime) override;
	void AimTowardsCrosshair();

	
	
};
