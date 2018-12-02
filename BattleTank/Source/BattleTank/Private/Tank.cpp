// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Classes/Camera/CameraComponent.h"
#include "Classes/GameFramework/SpringArmComponent.h"
#include "Classes/Components/SceneComponent.h"
#include "Classes/Components/StaticMeshComponent.h"
#include "Classes/Components/BoxComponent.h"
#include "TankAimingComponent.h"
#include "TankBarrelComponent.h"
#include "Runtime/Engine/Classes/Components/InputComponent.h"
#include "Projectile.h"
#include "Classes/Engine/World.h"
#include "TankMovementComponent.h"
#include "Runtime/Engine/Public/TimerManager.h"

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
	//BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	//BoxCollision->SetupAttachment(RootComponent);
	//BoxCollision->SetBoxExtent(FVector(400, 400, 100));
	SM_Body->SetupAttachment(RootComponent);
	SM_Body->SetSimulatePhysics(true);
	SM_Body->SetMassOverrideInKg(NAME_None, 40000.0f);
	SM_Body->SetEnableGravity(true);
	Gimbal->SetupAttachment(SM_Body);
	SpringArm->SetupAttachment(Gimbal);
	SpringArm->bUsePawnControlRotation = false;
	Camera->SetupAttachment(SpringArm);
	LaunchSpeed = 100000.0f;
	ReloadTimeInSeconds = 2.0f;
}

void ATank::SetBarrelReference(UTankBarrelComponent * BarrelRef)
{
	if (BarrelRef)
		TankAimingComponent->SetBarrelReference(BarrelRef);
		Barrel = BarrelRef;
}

void ATank::SetTurretReference(UTankTurretComponent * Turret)
{
	if (Turret)
	{
		TurretComp = Turret;
		TankAimingComponent->SetTurretReference(TurretComp);
	}
}

void ATank::Fire()
{
	bool IsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	if (Barrel && IsReloaded)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(DefaultProjectile,
				Barrel->GetSocketLocation("S_Muzzle"),
				Barrel->GetSocketRotation("S_Muzzle"),
				SpawnParams
				);	
			if (Projectile)
			{
				Projectile->Launch(LaunchSpeed);
				LastFireTime = FPlatformTime::Seconds();
				Reload();
			}
	}
}


// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}


void ATank::Reload()
{
	IsReloaded = false;
	FTimerHandle ReloadTimerHandle;
	TankAimingComponent->FiringState = EFiringState::Reloading;
	GetWorldTimerManager().SetTimer(ReloadTimerHandle, this, &ATank::SetReloadedAndFiringState, ReloadTimeInSeconds, false, 0);
}

void ATank::SetReloadedAndFiringState()
{
	IsReloaded = true;
	TankAimingComponent->FiringState = EFiringState::Reloaded;
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ATank::Fire);

}

void ATank::AimAt(FVector Location)
{
	TankAimingComponent->AimAt(Location, LaunchSpeed);
}

