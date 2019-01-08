// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Classes/Components/StaticMeshComponent.h"
#include "Classes/GameFramework/ProjectileMovementComponent.h"
#include "Classes/Components/SphereComponent.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "Classes/Engine/World.h"
#include "Classes/Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_Projectile"));
	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	LaunchBlastFX = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Launch Blast FX"));
	ProjectileMovementComp->bAutoActivate = false;
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	SetRootComponent(ProjectileMesh);
	CollisionSphere->SetupAttachment(ProjectileMesh);
	CollisionSphere->SetNotifyRigidBodyCollision(true);
	CollisionSphere->SetCollisionProfileName("Projectile");
	ProjectileMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LaunchBlastFX->AttachTo(CollisionSphere);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::Launch()
{
	ProjectileMovementComp->SetVelocityInLocalSpace(FVector::ForwardVector * LaunchSpeed);
	ProjectileMovementComp->Activate();
}

