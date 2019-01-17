// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthComponent.h"
#include "Classes/GameFramework/Actor.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	MaxHealth = 100;
	CurrentHealth = MaxHealth;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
}

void UHealthComponent::TakeDamage(AActor * DamagedActor, float Damage, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser)
{
	int32 DamagePoints = FMath::RoundToInt(Damage);
	CurrentHealth = FMath::Clamp(CurrentHealth - DamagePoints, 0, MaxHealth);
	if (CurrentHealth == 0)
	{
		OnDeath.Broadcast();
	}
}

