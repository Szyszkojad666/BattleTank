// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BattleTank_AIController.generated.h"

class ATank;
class UTankMovementComponent;
class UTankAimingComponent;
class APawn;
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

	UFUNCTION()
	void OnPawnDeath();

	ATank* GetPlayerTank();
	
	virtual void Tick(float DeltaTime) override;
	
	void AimTowardsCrosshair();
	
	virtual FPathFollowingRequestResult MoveTo(const FAIMoveRequest& MoveRequest, FNavPathSharedPtr* OutPath = nullptr) override;
	
	virtual void SetPawn(APawn* InPawn) override;

private:
	
	UTankMovementComponent* TankMovementComp;

	UTankAimingComponent* TankAimingComp;
	
	APawn* ControlledPawn;

	ATank* PlayerTank;

	void BeginPlay() override;

	void Fire();
};
