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
	Locked,
	OutOfAmmo
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
	
	UPROPERTY(EditDefaultsOnly)
	int Ammo = 10;
	
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrelComponent* BarrelRef, UTankTurretComponent* TurretRef);

	UFUNCTION(BlueprintCallable, Category = "Aiming")
	void Fire();

	UFUNCTION(BlueprintCallable, Category = "Aiming")
	void AimAt(FVector Location);

	UFUNCTION(BlueprintPure, Category = "Aiming")
	FORCEINLINE EFiringState GetFiringState() const { return FiringState; }

	UFUNCTION(BlueprintPure, Category = "Aiming")
	FORCEINLINE int GetAmmo() const { return Ammo; }

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	
	FVector AimDirection;
	UTankBarrelComponent* Barrel;
	UTankTurretComponent* Turret;
	bool IsReloaded = true;
	virtual void BeginPlay() override;
	void Reload();
	void IsAiming();

private: 
	
	UPROPERTY(EditDefaultsOnly)
	float ReloadTimeInSeconds = 1.0f;

	void MoveBarrel(FVector ShotDirection);
	void SetReloadedAndFiringState();
};
