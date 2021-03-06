// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrackComponent.generated.h"

class ASprungWheel;
class ASpawnPointComponent;
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

	float TankMaxDrivingForce;

	FORCEINLINE UFUNCTION()
	void SetTrackDrivingForce(float InDrivingForce) { TankMaxDrivingForce = InDrivingForce; }

private:

	UTankTrackComponent();

	TArray<class ASprungWheel*> GetWheels() const;

protected:

	void DriveTrack(float CurrentThrottle);

	UStaticMeshComponent* OwnerRoot;

	virtual void BeginPlay() override;
};
