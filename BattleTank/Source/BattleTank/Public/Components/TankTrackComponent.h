// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrackComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrackComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = Input)
		void SetThrottle(float Throttle);

	UFUNCTION()
		void OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	float TankMaxDrivingForce;

	FORCEINLINE UFUNCTION()
	void SetTrackDrivingForce(float InDrivingForce) { TankMaxDrivingForce = InDrivingForce; }

private:

	UTankTrackComponent();

protected:
	float CalculateSlippageSpeed();
	FVector CalculateCorrection();
	void ApplySideMovementCorrection();
	void DriveTrack();
	UStaticMeshComponent* OwnerRoot;
	virtual void BeginPlay() override;
	float CurrentThrottle = 0;

};
