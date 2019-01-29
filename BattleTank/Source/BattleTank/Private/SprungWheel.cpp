// Fill out your copyright notice in the Description page of Project Settings.

#include "SprungWheel.h"
#include "Classes/PhysicsEngine/PhysicsConstraintComponent.h"
#include "Classes/Components/StaticMeshComponent.h"
#include "Classes/Components/SphereComponent.h"
#include "Classes/Engine/World.h"


// Sets default values
ASprungWheel::ASprungWheel()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;
	Wheel = CreateDefaultSubobject<USphereComponent>(TEXT("Wheel"));
	Axle = CreateDefaultSubobject<USphereComponent>(TEXT("Axle"));
	Spring = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Spring"));
	AxleConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("AxleConstraint"));
	RootComponent = Spring;
	Axle->SetupAttachment(Spring);
	Wheel->SetupAttachment(Axle);
	Wheel->SetNotifyRigidBodyCollision(true);
	Wheel->SetSimulatePhysics(true);
	Wheel->SetCollisionProfileName("PhysicsBody");
	Wheel->SetHiddenInGame(false);
	Wheel->SetVisibility(true);
	AxleConstraint->SetupAttachment(Axle);
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	Wheel->OnComponentHit.AddDynamic(this, &ASprungWheel::OnHit);
	SetupConstraints();
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetWorld()->TickGroup == TG_PostPhysics)
	{
		TotalForceMagnitude = 0;
	}
}

void ASprungWheel::AddDrivingForce(float Magnitude)
{
	TotalForceMagnitude += Magnitude;
}

void ASprungWheel::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	ApplyForce();
}

void ASprungWheel::SetupConstraints()
{
	if (GetAttachParentActor())
	{
		UPrimitiveComponent* PrimitiveComp = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
		if (PrimitiveComp)
		{
			Spring->SetConstrainedComponents(PrimitiveComp, NAME_None, Axle, NAME_None);
		}
	}
	AxleConstraint->SetConstrainedComponents(Axle, NAME_None, Wheel, NAME_None);
}

void ASprungWheel::ApplyForce()
{
	Wheel->AddForce(Axle->GetForwardVector() * TotalForceMagnitude);
}

