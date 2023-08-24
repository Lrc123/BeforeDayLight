// Fill out your copyright notice in the Description page of Project Settings.


#include "BDLAttributeComponent.h"

#include "MathUtil.h"

// Sets default values for this component's properties
UBDLAttributeComponent::UBDLAttributeComponent() : MaxHealth(100.f), Health(MaxHealth)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	// ...
}

bool UBDLAttributeComponent::IsAlive()
{
	return Health > 0.0f;
}


bool UBDLAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{
	float oldHealth = Health;
	Health = FMathf::Clamp(Health + Delta, 0.0f, MaxHealth);
	float deltaHealth = Health - oldHealth;

	OnHealthChanged.Broadcast(InstigatorActor, this, Health, Delta);

	return deltaHealth != 0;
}

bool UBDLAttributeComponent::IsFullHealth() const
{
	return MaxHealth == Health;
}

bool UBDLAttributeComponent::IsActorAlive(AActor* Actor)
{
	UBDLAttributeComponent* AttributeComp = GetAttributes(Actor);
	if(AttributeComp)
	{
		return AttributeComp->IsAlive();
	}
	return false;
}

UBDLAttributeComponent* UBDLAttributeComponent::GetAttributes(AActor* FromActor)
{
	if(FromActor){
		return FromActor->FindComponentByClass<UBDLAttributeComponent>();
	}
	return nullptr;
}

float UBDLAttributeComponent::GetMaxHealth() const
{
	return MaxHealth;
}

float UBDLAttributeComponent::GetCurHealth() const
{
	return Health;
}


