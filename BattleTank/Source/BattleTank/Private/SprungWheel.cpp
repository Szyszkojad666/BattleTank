// Fill out your copyright notice in the Description page of Project Settings.

#include "SprungWheel.h"
#include "Classes/PhysicsEngine/PhysicsConstraintComponent.h"
#include "Classes/Components/StaticMeshComponent.h"


// Sets default values
ASprungWheel::ASprungWheel()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel"));
	Spring = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Spring"));
	RootComponent = Spring;
	Wheel->SetupAttachment(Spring);
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	if (GetAttachParentActor())
	{
		UPrimitiveComponent* PrimitiveComp = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
		if (PrimitiveComp)
		{
			Spring->SetConstrainedComponents(PrimitiveComp, NAME_None, Wheel, NAME_None);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Null"));
	}
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

