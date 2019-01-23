// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnPointComponent.h"
#include "SprungWheel.h"
#include "Classes/Engine/World.h"
#include "Classes/GameFramework/Actor.h"
#include "Classes/Kismet/GameplayStatics.h"

// Sets default values for this component's properties
USpawnPointComponent::USpawnPointComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USpawnPointComponent::BeginPlay()
{
	Super::BeginPlay();
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	auto NewActor = GetWorld()->SpawnActorDeferred<AActor>(ActorToSpawn,GetComponentTransform(), GetOwner());
	if (NewActor)
	{
		NewActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
	}
	UGameplayStatics::FinishSpawningActor(NewActor, GetComponentTransform());
}


// Called every frame
void USpawnPointComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

