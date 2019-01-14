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
class UTankTrackComponent;

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

	void InitializeAimingComponentVariables();

	void InitializeMovementComponentVariables();

	int32 TankCurrentHealth;

public:	
	// Getter functions

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UTankTurretComponent* GetTurret() const { if (TurretComp) return TurretComp; else return nullptr; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UTankMovementComponent* GetTankMovementComponent() const { return TankMovementComp; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UTankAimingComponent* GetTankAimingComponent() const { return TankAimingComponent; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetMaxHealth() const { return TankMaxHealth; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetCurrentHealth() const { return TankCurrentHealth; }

	//Max force on track in newtons
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float TrackMaxDrivingForce = 40000000;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 TankMaxHealth;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UCameraComponent* Camera;
	
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

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

private:
	ATank();
};
