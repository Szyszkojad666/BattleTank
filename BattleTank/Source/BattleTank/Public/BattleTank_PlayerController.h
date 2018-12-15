// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BattleTank_PlayerController.generated.h"



class ATank;
class UTankAimingComponent;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ABattleTank_PlayerController : public APlayerController
{
	GENERATED_BODY()


public:

void AimTowardsCrosshair();

UPROPERTY(EditDefaultsOnly)
float AimRange;

UPROPERTY(EditDefaultsOnly)
float AimPitchOffset;

UPROPERTY(EditDefaultsOnly)
float CrosshairXLocation;

UPROPERTY(EditDefaultsOnly)
float CrosshairYLocation;

private:
	
	ABattleTank_PlayerController();
	ATank* ControlledTank;
	virtual void Tick(float DeltaTime) override;

protected:
// Called when the game starts or when spawned
	void BeginPlay() override;
	void GetAimLocation();
	void Fire();
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE ATank* GetControlledTank() const { if (ControlledTank) return ControlledTank; else return nullptr; }

	UTankAimingComponent* TankAimingComponent;
	
	virtual void SetupInputComponent();
};
