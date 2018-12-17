// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BattleTank_AIController.generated.h"

class ATank;
class UTankMovementComponent;
class UTankAimingComponent;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ABattleTank_AIController : public AAIController
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintPure, Category = "Aiming")
	FORCEINLINE UTankAimingComponent* GetTankAimingComponent() const { return TankAimingComp; }

	ATank* GetPlayerTank();
	virtual void Tick(float DeltaTime) override;
	void AimTowardsCrosshair();
	virtual FPathFollowingRequestResult MoveTo(const FAIMoveRequest& MoveRequest, FNavPathSharedPtr* OutPath = nullptr) override;

private:
	
	UTankMovementComponent* TankMovementComp;
	UTankAimingComponent* TankAimingComp;
	
	ATank* ControlledTank;
	ATank* PlayerTank;

	void BeginPlay() override;
	void Fire();
};
