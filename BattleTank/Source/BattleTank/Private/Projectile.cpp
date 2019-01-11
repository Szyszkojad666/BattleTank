// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Classes/Components/StaticMeshComponent.h"
#include "Classes/GameFramework/ProjectileMovementComponent.h"
#include "Classes/Components/SphereComponent.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "Classes/Engine/World.h"
#include "Classes/Particles/ParticleSystemComponent.h"
#include "Classes/PhysicsEngine/RadialForceComponent.h"
#include "Classes/Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_Projectile"));
	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	LaunchBlastFX = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Launch Blast FX"));
	ImpactBlastFX = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Impact Blast FX"));
	ProjectileMovementComp->bAutoActivate = false;
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	SetRootComponent(CollisionSphere);
	ProjectileMesh->SetupAttachment(CollisionSphere);
	CollisionSphere->SetNotifyRigidBodyCollision(true);
	CollisionSphere->SetCollisionProfileName("Projectile");
	//CollisionSphere->SetSimulatePhysics(true);
	CollisionSphere->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	ProjectileMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LaunchBlastFX->SetupAttachment(CollisionSphere);
	ImpactBlastFX->SetupAttachment(CollisionSphere);
	ImpactBlastFX->SetAutoActivate(false);
	RadialForce = CreateDefaultSubobject<URadialForceComponent>(TEXT("Radial Force"));
	RadialForce->SetupAttachment(CollisionSphere);
	RadialForce->SetAutoActivate(false);
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

void AProjectile::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	LaunchBlastFX->Deactivate();
	ImpactBlastFX->Activate();
	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ProjectileMesh->SetHiddenInGame(true);
	SetLifeSpan(3.0f);
	RadialForce->Activate();
	RadialForce->FireImpulse();
	UGameplayStatics::ApplyRadialDamage(
		this,
		ProjectileDamage,
		GetActorLocation(),
		RadialForce->Radius,
		UDamageType::StaticClass(),
		TArray<AActor*>(),
		GetOwner()
	);
}

