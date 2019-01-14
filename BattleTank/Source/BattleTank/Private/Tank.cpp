// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Classes/Camera/CameraComponent.h"
#include "Classes/GameFramework/SpringArmComponent.h"
#include "Classes/Components/SceneComponent.h"
#include "Classes/Components/StaticMeshComponent.h"
#include "Classes/Components/BoxComponent.h"
#include "TankAimingComponent.h"
#include "TankBarrelComponent.h"
#include "TankTurretComponent.h"
#include "TankTrackComponent.h"
#include "Runtime/Engine/Classes/Components/InputComponent.h"
#include "Projectile.h"
#include "Classes/Engine/World.h"
#include "TankMovementComponent.h"

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Gimbal = CreateDefaultSubobject<USceneComponent>(TEXT("Gimbal"));
	SM_Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_Body"));
	TankMovementComp = CreateDefaultSubobject<UTankMovementComponent>(TEXT("TankMovementComponent"));
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(TEXT("TankAimingComponent"));
	TurretComp = CreateDefaultSubobject<UTankTurretComponent>(TEXT("Turret"));
	Barrel = CreateDefaultSubobject<UTankBarrelComponent>(TEXT("Barrel"));
	TrackR = CreateDefaultSubobject<UTankTrackComponent>(TEXT("TrackR"));
	TrackL = CreateDefaultSubobject<UTankTrackComponent>(TEXT("TrackL"));
	//BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	//BoxCollision->SetupAttachment(RootComponent);
	//BoxCollision->SetBoxExtent(FVector(400, 400, 100));
	SM_Body->SetupAttachment(RootComponent);
	SM_Body->SetSimulatePhysics(true);
	SM_Body->SetMassOverrideInKg(NAME_None, 40000.0f);
	SM_Body->SetEnableGravity(true);
	SM_Body->SetLinearDamping(0.5);
	SM_Body->SetAngularDamping(0.8);
	Gimbal->SetupAttachment(SM_Body);
	SpringArm->SetupAttachment(Gimbal);
	SpringArm->bUsePawnControlRotation = false;
	Camera->SetupAttachment(SpringArm);
	ReloadTimeInSeconds = 2.0f;
	TankMaxHealth = 100.0f;
	TankCurrentHealth = TankMaxHealth;
}

float ATank::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagePoints = FMath::RoundToInt(Damage);
	TankCurrentHealth= FMath::Clamp(TankCurrentHealth - DamagePoints, 0, TankMaxHealth);
	if (TankCurrentHealth == 0)
	{
		Destroy();
	}
	return Damage;
}

void ATank::InitializeAimingComponentVariables()
{
	if (ensure(Barrel && TurretComp))
	{
		TankAimingComponent->Initialize(Barrel, TurretComp);
	}
}

void ATank::InitializeMovementComponentVariables()
{
	if (ensure(TrackR && TrackL))
	{
		TankMovementComp->Initialise(TrackL, TrackR);
	}
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	InitializeAimingComponentVariables();
	InitializeMovementComponentVariables();
}


