// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"


class UTankTrackComponent;
class ATank;
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
		void MoveForward(float Throw);

	UFUNCTION(BlueprintCallable)
		void TurnRight(float Throw);

	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
	
	
private:
	UTankTrackComponent* LeftTrack = nullptr;
	UTankTrackComponent* RightTrack = nullptr;
	
protected:
	virtual void BeginPlay() override;

	ATank* OwnerTank = nullptr;
};
