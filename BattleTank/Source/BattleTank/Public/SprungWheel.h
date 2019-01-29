// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

class UStaticMeshComponent;
class UPhysicsConstraintComponent;
class USphereComponent;

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();

	virtual void Tick(float DeltaTime) override;

	void AddDrivingForce(float Magnitude);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	//Components

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* Axle;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* Wheel;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPhysicsConstraintComponent* Spring;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPhysicsConstraintComponent* AxleConstraint;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void SetupConstraints();

	void ApplyForce();

	float TotalForceMagnitude = 0;
};
