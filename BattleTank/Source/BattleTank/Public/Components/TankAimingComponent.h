// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Reloaded,
	Aiming,
	Locked
};

class UTankBarrelComponent;
class UTankTurretComponent;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), BlueprintType)
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPROPERTY(BlueprintReadOnly)
	EFiringState FiringState = EFiringState::Reloaded;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		float TurretRotationSpeed = 20;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		float BarrelElevationSpeed = 20;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AProjectile> DefaultProjectileClass;
	
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable)
	void Initialize(UTankBarrelComponent* BarrelRef, UTankTurretComponent* TurretRef);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AimAt(FVector Location);

	void Fire();


	
protected:
	
	FVector AimDirection;
	UTankBarrelComponent* Barrel;
	UTankTurretComponent* Turret;
	bool IsReloaded = true;
	virtual void BeginPlay() override;
	void Reload();
	void IsAiming();

private: 
	
	float ReloadTimeInSeconds = 1.0f;
	void MoveBarrel(FVector ShotDirection);
	void SetReloadedAndFiringState();
};
