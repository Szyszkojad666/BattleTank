// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"


class UTankTrackComponent;
/**
 * 
 */
UCLASS(ClassGroup = (TankMovement), meta = (BlueprintSpawnableComponent), BlueprintType)
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MaxDrivingForce = 40000000.0f;
	
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

};
