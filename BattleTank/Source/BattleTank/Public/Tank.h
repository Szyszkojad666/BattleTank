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

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UTankAimingComponent* TankAimingComponent;

	UStaticMeshComponent* Barrel;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AimAt(FVector Location);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UCameraComponent* Camera;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LaunchSpeed;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		USceneComponent* Gimbal;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* SM_Body;

	UPROPERTY(BlueprintAssignable)
		FAimBarrel AimBarrel;

	UFUNCTION(BlueprintCallable)
		void SetBarrelReference(UStaticMeshComponent* BarrelRef);

private:
	ATank();
};
