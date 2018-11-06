// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class ATank;

class UTankBarrelComponent;
class UTankTurretComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void SetBarrelReference(UTankBarrelComponent* BarrelRef);
	void SetTurretReference(UTankTurretComponent* TurretRef);



	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AimAt(FVector Location, float LaunchSpeed);


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UTankBarrelComponent* Barrel;
	UTankTurretComponent* Turret;

	ATank* MyOwnerTank;

private: 
	void MoveBarrel(FVector ShotDirection);

	
	
};
