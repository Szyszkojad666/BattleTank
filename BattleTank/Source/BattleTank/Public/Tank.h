// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAimBarrel, FRotator, Rotation);

class USpringArmComponent;
class UCameraComponent;
class USceneComponent;
class UStaticMesh;
class UBoxComponent;
class UTankAimingComponent;
class UTankBarrelComponent;
class UTankTurretComponent;
class UTankMovementComponent;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UTankMovementComponent* TankMovementComp;
	
	UTankBarrelComponent* Barrel;

	UTankTurretComponent* TurretComp;

	bool IsReloaded = true;

	void Reload();

	void SetReloadedAndFiringState();
	
public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AimAt(FVector Location);

	//Max force on track in newtons
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		float TrackMaxDrivingForce = 40000000;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UCameraComponent* Camera;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LaunchSpeed;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AProjectile> DefaultProjectile;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		USceneComponent* Gimbal;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* SM_Body;

	UPROPERTY(BlueprintAssignable)
		FAimBarrel AimBarrel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ReloadTimeInSeconds;

	UFUNCTION(BlueprintCallable)
		void InitializeAimingComponentVariables(UTankBarrelComponent* BarrelRef, UTankTurretComponent* TurretRef);

	UFUNCTION(BlueprintCallable)
		FORCEINLINE UTankTurretComponent* GetTurret() { if (TurretComp) return TurretComp; else return nullptr; }

	UFUNCTION(BlueprintCallable)
		void Fire();

	UFUNCTION(BlueprintCallable)
		FORCEINLINE UTankMovementComponent* GetTankMovementComponent() { return TankMovementComp; }
private:
	ATank();
};
