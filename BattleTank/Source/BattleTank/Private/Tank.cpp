// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Classes/Camera/CameraComponent.h"
#include "Classes/GameFramework/SpringArmComponent.h"
#include "Classes/Components/SceneComponent.h"
#include "Classes/Components/StaticMeshComponent.h"
#include "Classes/Components/BoxComponent.h"
#include "TankAimingComponent.h"

void ATank::SetBarrelReference(UStaticMeshComponent * BarrelRef)
{
	if (BarrelRef)
		TankAimingComponent->SetBarrelReference(BarrelRef);
}

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Gimbal = CreateDefaultSubobject<USceneComponent>(TEXT("Gimbal"));
	SM_Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_Body"));
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(TEXT("TankAimingComponent"));
	//BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	//BoxCollision->SetupAttachment(RootComponent);
	//BoxCollision->SetBoxExtent(FVector(400, 400, 100));
	SM_Body->SetupAttachment(RootComponent);
	SM_Body->SetSimulatePhysics(true);
	SM_Body->SetMassOverrideInKg(NAME_None, 40000.0f);
	Gimbal->SetupAttachment(SM_Body);
	SpringArm->SetupAttachment(Gimbal);
	SpringArm->bUsePawnControlRotation = false;
	Camera->SetupAttachment(SpringArm);
	LaunchSpeed = 100000.0f;

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector Location)
{
	AimAtLocation.Broadcast(Location);
	TankAimingComponent->AimAt(Location, LaunchSpeed);
}

