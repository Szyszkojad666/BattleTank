// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BattleTank_PlayerController.generated.h"


class ATank;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ABattleTank_PlayerController : public APlayerController
{
	GENERATED_BODY()


public:
UFUNCTION(BlueprintCallable)
FORCEINLINE ATank* GetControlledTank() const { if (ControlledTank) return ControlledTank; else return nullptr; }
virtual void Tick(float DeltaTime) override;
void AimTowardsCrosshair();
	

UPROPERTY(EditDefaultsOnly)
float AimRange;

private:
	ABattleTank_PlayerController();
	ATank* ControlledTank;
	
	
protected:
// Called when the game starts or when spawned
	void BeginPlay() override;
	FHitResult GetAimLocation() const;
	
	
};
