// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAimBarrel, FRotator, Rotation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTankDeath);

class USpringArmComponent;
class UCameraComponent;
class USceneComponent;
class UStaticMesh;
class UBoxComponent;
class UTankAimingComponent;
class UTankBarrelComponent;
class UTankTurretComponent;
class UTankMovementComponent;
class UTankTrackComponent;
class UHealthComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UTankMovementComponent* TankMovementComp;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UTankBarrelComponent* Barrel;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UTankTurretComponent* TurretComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UTankTrackComponent* TrackR;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UTankTrackComponent* TrackL;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UHealthComponent* HealthComponent;

	void InitializeAimingComponentVariables();

	void InitializeMovementComponentVariables();

public:	
	// Getter functions

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UTankTurretComponent* GetTurret() const { if (TurretComp) return TurretComp; else return nullptr; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UTankMovementComponent* GetTankMovementComponent() const { return TankMovementComp; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UTankAimingComponent* GetTankAimingComponent() const { return TankAimingComponent; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UHealthComponent* GetHealthComponent() const { return HealthComponent; }

	//Max force on track in newtons
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float TrackMaxDrivingForce = 40000000;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UCameraComponent* Camera;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USceneComponent* Gimbal;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* SM_Body;

	UPROPERTY(BlueprintAssignable)
	FAimBarrel AimBarrel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ReloadTimeInSeconds;

private:
	ATank();
};
