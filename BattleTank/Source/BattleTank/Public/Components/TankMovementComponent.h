// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrackComponent;
/**
 * 
 */
UCLASS(ClassGroup = (TankMovement), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = Setup)
		void Initialise(UTankTrackComponent* LeftTrackToSet, UTankTrackComponent* RightTrackToSet);
	
	UFUNCTION(BlueprintCallable)
		void MoveForward(float Throw, float Speed);

	UFUNCTION(BlueprintCallable)
		void TurnRight(float Throw, float Speed);

	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
	
	
private:
	UTankTrackComponent* LeftTrack = nullptr;
	UTankTrackComponent* RightTrack = nullptr;
	
};
